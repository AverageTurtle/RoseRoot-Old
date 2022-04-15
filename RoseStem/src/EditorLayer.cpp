#include "EditorLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RoseRoot/Scene/SceneSerializer.h"
#include "RoseRoot/Utils/PlatformUtils.h"
#include "RoseRoot/Math/Math.h"

#include "State/StateManager.h"
#include "State/SceneManager.h"
#include "ImGuizmo.h"


namespace RoseRoot {
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
	}

	void EditorLayer::OnAttach()
	{
		RR_PROFILE_FUNCTION();
		g_State.Project = CreateRef<Project>();

		Application::Get().GetWindow().SetWindowIcon("Resources/icon.png");
		m_IconPlay = Texture2D::Create("Resources/Icons/PlayButton.png");
		m_IconStop = Texture2D::Create("Resources/Icons/StopButton.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);


		auto commandLineArgs = Application::Get().GetCommandLineArgs();
		if (commandLineArgs.Count > 1)
		{
			auto projectFilePath = commandLineArgs[1];
			g_State.Project = CreateRef<Project>(projectFilePath);
		}

		m_ContentBrowserPanel.SetAssetPath(g_State.Project->GetAssetPath());
		m_SceneHierarchyPanel.SetAssetPath(g_State.Project->GetAssetPath());
		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

		ResetToProjectSettings();
		SceneManager::NewScene(&m_SceneHierarchyPanel);
	}

	void EditorLayer::OnDetach()
	{
		RR_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		RR_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			g_State.ViewportSize.x > 0.0f && g_State.ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != g_State.ViewportSize.x || spec.Height != g_State.ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)g_State.ViewportSize.x, (uint32_t)g_State.ViewportSize.y);
			m_EditorCamera.SetViewportSize(g_State.ViewportSize.x, g_State.ViewportSize.y);
			g_State.ActiveScene->OnViewportResize((uint32_t)g_State.ViewportSize.x, (uint32_t)g_State.ViewportSize.y);
		}

		// Update
		m_EditorCamera.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		// Clear our entity ID attachment to -1
		m_Framebuffer->ClearAttachment(1, -1);

		// Update scene
		if (g_State.SceneState == SceneState::Edit)
			g_State.ActiveScene->OnUpdateEditor(ts, m_EditorCamera);
		else if (g_State.SceneState == SceneState::Play) {
			m_GizmoType = -1;
			g_State.ActiveScene->OnUpdateRuntime(ts);
		}
			

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			m_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, g_State.ActiveScene.get());
		}

		OnOverlayRender();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		RR_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 320.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
				if (ImGui::MenuItem("New Project"))
					NewProject();
				if (ImGui::MenuItem("Open Project"))
					OpenProject();

				if (ImGui::MenuItem("New Scene", "Ctrl+N"))
					SceneManager::NewScene(&m_SceneHierarchyPanel);

				if (ImGui::MenuItem("Open Scene", "Ctrl+O"))
					SceneManager::OpenScene(&m_SceneHierarchyPanel);

				if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
					SceneManager::SaveScene();

				if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S"))
					SceneManager::SaveSceneAs();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Scene Settings", "Ctrl+L"))
					m_SceneSettingsOpen = !m_SceneSettingsOpen;
				if (ImGui::MenuItem("Project Settings", "Ctrl+P"))
					m_ProjectSettingsOpen = !m_ProjectSettingsOpen;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		m_SceneHierarchyPanel.OnImGuiRender();
		m_ContentBrowserPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		g_State.ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ g_State.ViewportSize.x, g_State.ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				SceneManager::OpenScene(g_State.Project->GetAssetPath() / path, &m_SceneHierarchyPanel);
			}
			ImGui::EndDragDropTarget();
		}

		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

			// Camera

			// Runtime camera from entity
			// auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			// const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			// const glm::mat4& cameraProjection = camera.GetProjection();
			// glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Editor camera
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}


		ImGui::End();
		ImGui::PopStyleVar();

		UI_Toolbar();
		if (m_SceneSettingsOpen)
			SceneSettingsWindow();
		if (m_ProjectSettingsOpen)
			ProjectSettingsWindow();

		ImGui::End();
	}
	
	void EditorLayer::UI_Toolbar()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

		ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		float size = ImGui::GetWindowHeight() - 4.0f;
		Ref<Texture2D> icon = g_State.SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
		if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(size, size), ImVec2(0,0), ImVec2(1,1), 0))
		{
			if (g_State.SceneState == SceneState::Edit)
				SceneManager::OnScenePlay(&m_SceneHierarchyPanel);
			else if (g_State.SceneState == SceneState::Play)
				SceneManager::OnSceneStop(&m_SceneHierarchyPanel);
		}
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_EditorCamera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(RR_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(RR_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool alt = Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt);

		switch (e.GetKeyCode())
		{
		case Key::N:
		{
			if (control)
				SceneManager::NewScene(&m_SceneHierarchyPanel);

			break;
		}
		case Key::O:
		{
			if (control)
				SceneManager::OpenScene(&m_SceneHierarchyPanel);

			break;
		}
		case Key::S:
		{
			if (control && alt)
				SceneManager::SaveSceneAs();
			if (control)
				SceneManager::SaveScene();

			break;
		}

		case Key::D:
		{
			if (control)
				OnDuplicateEntity();

			break;
		}
		case Key::L:
		{
			m_SceneSettingsOpen = !m_SceneSettingsOpen;
			break;
		}
		case Key::P:
		{
			m_ProjectSettingsOpen = !m_ProjectSettingsOpen;
			break;
		}
			// Gizmos
		case Key::Q:
		{
			if (!ImGuizmo::IsUsing() && g_State.SceneState == SceneState::Edit)
				m_GizmoType = -1;
			break;
		}
		case Key::W:
		{
			if (!ImGuizmo::IsUsing() && g_State.SceneState == SceneState::Edit)
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		}
		case Key::E:
		{
			if (!ImGuizmo::IsUsing() && g_State.SceneState == SceneState::Edit)
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		}
		case Key::R:
		{
			if (!ImGuizmo::IsUsing() && g_State.SceneState == SceneState::Edit)
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
		
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			if (m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
				m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}

	void EditorLayer::SceneSettingsWindow()
	{
		ImGui::Begin("Scene Settings");

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		std::strncpy(buffer, g_State.SceneName.c_str(), sizeof(buffer));
		if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
		{
			g_State.SceneName = std::string(buffer);
			g_State.EditorScene->SetName(g_State.SceneName);
		}

		if (ImGui::TreeNodeEx("Physics2D"))
		{


			if (ImGui::DragFloat2("Gravity 2D", glm::value_ptr(g_State.Gravity)))
			{
				if (g_State.SceneState == SceneState::Edit)
					g_State.EditorScene->SetGravity2D(g_State.Gravity);
			}
			ImGui::TreePop();
		}

		ImGui::Checkbox("Show Colliders", &m_ShowPhysicsColliders);
		ImGui::End();
	}

	void EditorLayer::ProjectSettingsWindow()
	{
		ImGui::Begin("Project Settings");

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		std::strncpy(buffer, g_State.Project->GetName().c_str(), sizeof(buffer));
		if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
		{
			g_State.Project->SetName(std::string(buffer));
		}

		ImGui::PushItemWidth(70);
		ImGui::InputInt("Number of Scenes", &m_NumberOfScenes, 0, 100);
		ImGui::PopItemWidth();

		if (ImGui::TreeNodeEx("Scene Index"))
		{
			for (int i = 0; i < m_NumberOfScenes; i++) {
				if (m_ScenePathsBuffer.find(i) == m_ScenePathsBuffer.end()) {
					m_ScenePathsBuffer.insert(std::make_pair(i, std::pair<int, std::filesystem::path>(i, "no-scene")));
				}

				ImGui::PushItemWidth(70);
				std::string index = "##Index ";
				index += std::to_string(i);
				ImGui::InputInt(index.c_str(), &m_ScenePathsBuffer.at(i).first, 0, 100);
				ImGui::PopItemWidth();

				ImGui::SameLine();

				std::string  scene = m_ScenePathsBuffer.at(i).second.filename().string();
				ImGui::Button(scene.c_str(), ImVec2(150.0f, 0.0f));

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path scenePath = g_State.Project->GetAssetPath() / path;
						m_ScenePathsBuffer.at(i).second = scenePath;
					}
					ImGui::EndDragDropTarget();
				}
			}

			ImGui::TreePop();
		}

		ImGui::Text("");

		if (ImGui::Button("Save Project Settings", { 200, 30 }))
			SaveProjectSettings();
		

		if (ImGui::Button("Reset To Project Settings", { 200, 21 }))
			ResetToProjectSettings();
		
		ImGui::End();
	}

	void EditorLayer::ResetToProjectSettings()
	{
		m_ScenePathsBuffer.clear();

		m_NumberOfScenes = g_State.Project->GetSizeOfSceneIndex();

		auto sceneIndexPtr = g_State.Project->GetSceneIndexPtr();

		int i = 0;
		std::for_each(sceneIndexPtr->begin() , sceneIndexPtr->end(), [&](std::pair<int, std::filesystem::path> elements) {
			m_ScenePathsBuffer.insert(std::make_pair(i, elements));
			i++;
		});
	}

	void EditorLayer::SaveProjectSettings()
	{
		g_State.Project->ClearSceneIndex();
		for (int i = 0; i < m_NumberOfScenes; i++) {
			g_State.Project->SetSceneToIndex(m_ScenePathsBuffer.at(i).first, m_ScenePathsBuffer.at(i).second);
		}

		g_State.Project->SaveProject();
	}

	void EditorLayer::OnOverlayRender()
	{
		if (g_State.SceneState == SceneState::Play)
		{
			Entity camera = g_State.ActiveScene->GetPrimaryCameraEntity();
			if (camera) {
				Renderer2D::BeginScene(camera.GetComponent<CameraComponent>().Camera, camera.GetComponent<TransformComponent>().GetTransform());
			}
			
		}
		else
		{
			Renderer2D::BeginScene(m_EditorCamera);
		}

		if (m_ShowPhysicsColliders)
		{
			if (g_State.SceneState == SceneState::Play)
			{
				Entity camera = g_State.ActiveScene->GetPrimaryCameraEntity();
				Renderer2D::BeginScene(camera.GetComponent<CameraComponent>().Camera, camera.GetComponent<TransformComponent>().GetTransform());
			}
			else
			{
				Renderer2D::BeginScene(m_EditorCamera);
			}

			if (m_ShowPhysicsColliders)
			{
				// Box Colliders
				{
					auto view = g_State.ActiveScene->GetAllEntitiesWith<TransformComponent, BoxCollider2DComponent>();
					for (auto entity : view)
					{
						auto [tc, bc2d] = view.get<TransformComponent, BoxCollider2DComponent>(entity);

						glm::vec3 translation = tc.Translation + glm::vec3(bc2d.Offset, 0.001f);
						glm::vec3 scale = tc.Scale * glm::vec3(bc2d.Size * 2.0f, 1.0f);

						glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
							* glm::rotate(glm::mat4(1.0f), tc.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
							* glm::scale(glm::mat4(1.0f), scale);

						Renderer2D::DrawRect(transform, glm::vec4(0.2f, 0.2f, 1, 1));
					}
				}

				// Circle Colliders
				{
					auto view = g_State.ActiveScene->GetAllEntitiesWith<TransformComponent, CircleCollider2DComponent>();
					for (auto entity : view)
					{
						auto [tc, cc2d] = view.get<TransformComponent, CircleCollider2DComponent>(entity);

						glm::vec3 translation = tc.Translation + glm::vec3(cc2d.Offset, 0.001f);
						glm::vec3 scale = tc.Scale * glm::vec3(cc2d.Radius * 2.0f);

						glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
							* glm::scale(glm::mat4(1.0f), scale);

						Renderer2D::DrawCircle(transform, glm::vec4(0.2f, 0.2f, 1, 1), 0.05f);
					}
				}
			}

			Renderer2D::EndScene();
		}
	}

	

	void EditorLayer::NewProject()
	{
		//TODO Saftey net for unsaved scenes.
		//SaveScene();
		SceneManager::NewScene(&m_SceneHierarchyPanel);
		std::filesystem::path filepath = FileDialogs::SaveFile("Rose Project");
		if (!filepath.empty())
		{
			g_State.Project = CreateRef<Project>(filepath);
			m_ContentBrowserPanel.SetAssetPath(g_State.Project->GetAssetPath());
			m_SceneHierarchyPanel.SetAssetPath(g_State.Project->GetAssetPath());
		}	
	} 
	void EditorLayer::OpenProject()
	{
		//TODO Saftey net for unsaved scenes.
		//SaveScene();
		SceneManager::NewScene(&m_SceneHierarchyPanel);
		std::string filepath = FileDialogs::OpenFile("Rose Project (*.rproj)\0*.rproj\0");
		if (!filepath.empty()) {
			g_State.Project->OpenProject(filepath);
			m_ContentBrowserPanel.SetAssetPath(g_State.Project->GetAssetPath());
			m_SceneHierarchyPanel.SetAssetPath(g_State.Project->GetAssetPath());
			ResetToProjectSettings();
		}
	}

	void EditorLayer::OnDuplicateEntity()
	{
		if (g_State.SceneState != SceneState::Edit)
			return;

		if (m_SceneHierarchyPanel.GetSelectedEntity())
			g_State.EditorScene->DuplicateEntity(m_SceneHierarchyPanel.GetSelectedEntity());
	}
}