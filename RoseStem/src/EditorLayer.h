#pragma once
#include "RoseRoot.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#include "RoseRoot/Renderer/EditorCamera.h"

namespace RoseRoot {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void SceneSettingsWindow();
		void ProjectSettingsWindow();

		void ResetToProjectSettings();
		void SaveProjectSettings();

		void OnOverlayRender();

		void NewProject();
		void OpenProject();

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();
		void SaveScene();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();


		//UI Panels
		void UI_Toolbar();
	private:
		Project m_Project;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;
		Ref<Framebuffer> m_Framebuffer;

		Entity m_HoveredEntity;

		bool m_ShowPhysicsColliders = false;
		bool m_SceneSettingsOpen = true;
		bool m_ProjectSettingsOpen = true;

		//Project Buffer
		int m_NumberOfScenes = 0;
		std::unordered_map<int, std::pair<int, std::filesystem::path>> m_ScenePathsBuffer;

		EditorCamera m_EditorCamera;

		Ref<Texture2D> m_SpriteSheet, m_ViewTest;
		Ref<SubTexture2D> m_GrassTexture, m_StoneTexture, m_GlassTexture;

		std::string m_SceneName = "Untitled";
		glm::vec2 m_Gravity = { 0.0, -9.8 };

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState m_SceneState = SceneState::Edit;

		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		//Editor Resources
		Ref<Texture2D> m_IconPlay, m_IconStop;
	};
}
