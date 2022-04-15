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

		

		void OnDuplicateEntity();


		//UI Panels
		void UI_Toolbar();
	private:
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

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;
		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		//Editor Resources
		Ref<Texture2D> m_IconPlay, m_IconStop;
	};
}
