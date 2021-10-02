#pragma once
#include "RoseRoot.h"

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
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		entt::entity m_SquareEntity;

		Ref<Texture2D> m_SpriteSheet, m_ViewTest;
		Ref<SubTexture2D> m_GrassTexture, m_StoneTexture, m_GlassTexture;

		glm::vec4 m_Color = { 1.f, 1.f, 1.f, 1.f };

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		//Ref<Texure2D> m_Texture;
	};
}
