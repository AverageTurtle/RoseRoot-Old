#include "EditorLayer.h"
#include "imgui/imgui.h"

namespace VoxelEngine {
	//Temp draw cube
	void DrawCube(glm::vec3 position, glm::vec4 color, Ref<SubTexture2D> texture)
	{
		RendererVoxel::DrawQuadRotated(glm::vec3(0.f, 0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, color, texture, 1.f);
		RendererVoxel::DrawQuadRotated(glm::vec3(0.f, -0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, color, texture, 1.f);

		RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, 0.5f) + position, { 1.f, 1.f, 1.f }, color, texture, 1.f);
		RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, -0.5f) + position, { 1.f, 1.f, 1.f }, color, texture, 1.f);

		RendererVoxel::DrawQuadRotated(glm::vec3(0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, color, texture, 1.f);
		RendererVoxel::DrawQuadRotated(glm::vec3(-0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, color, texture, 1.f);
	}

	EditorLayer::EditorLayer(Window& window)
		: Layer("MainLayer"), m_Window(window), m_CameraController(16.f / 9.f)
	{
	}

	void EditorLayer::OnAttach()
	{
		VE_PROFILE_FUNCTION();

		m_CameraController.SetTracking(false);
		m_Window.SetCapturesMouse(false);

		m_SpriteSheet = Texture2D::Create("assets/textures/SpriteSheet.png");
		m_ViewTest = Texture2D::Create("assets/textures/ViewTest.png");

		m_GrassTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 0 }, { 16, 16 });
		m_StoneTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 0 }, { 16, 16 });
		m_GlassTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 0 }, { 16, 16 });

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);
	}


	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		VE_PROFILE_FUNCTION();

		m_CameraController.OnUpdate(ts);


		//Render
		RendererVoxel::ResetStats();
		m_Framebuffer->Bind();

		const int size = 128;
		if (m_Scene == 1)
		{
			RenderCommand::SetClearColor({ 0.5, 0.6, 0.9, 1 });
			RenderCommand::Clear();

			RendererVoxel::BeginScene(m_CameraController.GetCamera());

			static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

			for (int z = 0; z < size; z++)
			{
				for (int x = 0; x < size; x++)
				{
					DrawCube({ x - (float)size / 2, -2, z - (float)size / 2 }, m_Color, m_GrassTexture);
				}
			}
			DrawCube({ -6,  0, 0 }, m_Color, m_StoneTexture);
			DrawCube({ -6,  0, 2 }, m_Color, m_StoneTexture);
			DrawCube({ -6, -1, 0 }, m_Color, m_StoneTexture);
			DrawCube({ -6, -1, 1 }, m_Color, m_StoneTexture);
			DrawCube({ -6, -1, 2 }, m_Color, m_StoneTexture);
			DrawCube({ -6,  1, 0 }, m_Color, m_StoneTexture);
			DrawCube({ -6,  1, 1 }, m_Color, m_StoneTexture);
			DrawCube({ -6,  1, 2 }, m_Color, m_StoneTexture);

			DrawCube({ -6,  0, 1 }, m_Color, m_GlassTexture);

			//RendererVoxel::DrawQuad({ 0.f,0.f,-16.f }, { 16.f, 16.f, 0.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_GrassTexture, 16.f);

			RendererVoxel::EndScene();
		}
		else if (m_Scene == 2)
		{
			RenderCommand::SetClearColor({ 0.05, 0.05, 0.09, 1 });
			RenderCommand::Clear();
			RendererVoxel::BeginScene(m_CameraController.GetCamera());

			static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

			for (int z = 0; z < size; z++)
			{
				for (int x = 0; x < size; x++)
				{
					DrawCube({ x - (float)size / 2, -2, z - (float)size / 2 }, { m_Color.x / 2, m_Color.y / 2, m_Color.z / 2, m_Color.a }, m_GrassTexture);
				}
			}
			DrawCube({ 4,  0, 0 }, { m_Color.x / 2, m_Color.y / 2, m_Color.z / 2, m_Color.a }, m_GlassTexture);
			DrawCube({ 4, -1, 0 }, { m_Color.x / 2, m_Color.y / 2, m_Color.z / 2, m_Color.a }, m_GlassTexture);

			//RendererVoxel::DrawQuad({ 0.f,0.f,-16.f }, { 16.f, 16.f, 0.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_GrassTexture, 16.f);

			RendererVoxel::EndScene();
		}

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		VE_PROFILE_FUNCTION();

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
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
		ImGui::Begin("Settings");

		//TEMP
		ImGui::Text("TEST BUILD DO NOT DISTRUBUTE");

		ImGui::Text("Camera Fov: %.2f", m_CameraController.GetFOV());
		ImGui::Text("Camera Sensitivity: %.2f", m_CameraController.GetSensitivity());

		auto stats = RendererVoxel::GetStats();
		ImGui::Text("Renderer Voxel Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Object Color:", glm::value_ptr(m_Color));

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("View Port");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewPortSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewPortSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_CameraController.SetAspectRatio(viewportPanelSize.x/viewportPanelSize.y);
			RenderCommand::SetViewport(0, 0, viewportPanelSize.x, viewportPanelSize.y);
		}
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(VE_BIND_EVENT_FN(EditorLayer::KeyPressed));
	}
	bool EditorLayer::KeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == VE_KEY_ESCAPE)
		{
			if (e.GetRepeatCount() == 0)
			{
				if (m_Window.GetCapturesMouse())
				{
					m_CameraController.SetTracking(false);
					m_Window.SetCapturesMouse(false);
				}
				else
				{
					m_CameraController.SetTracking(true);
					m_Window.SetCapturesMouse(true);
				}
			}

		}

		if (e.GetKeyCode() == VE_KEY_I)
		{
			if (e.GetRepeatCount() == 0)
			{
				if (m_Scene == 1)
				{
					m_Scene = 2;
				}
				else
				{
					m_Scene = 1;
				}
			}

		}

		return false;
	}
}