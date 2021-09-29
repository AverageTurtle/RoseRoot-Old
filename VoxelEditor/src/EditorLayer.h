#pragma once
#include <VoxelEngine.h>

namespace VoxelEngine {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer(Window& window);
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

		bool KeyPressed(KeyPressedEvent& e);
	private:
		int m_Scene = 1;
		FlightCameraController m_CameraController;

		Window& m_Window;

		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_Framebuffer;
		Ref<VertexArray> m_VertexArray;

		Ref<Texture2D> m_SpriteSheet, m_ViewTest;
		Ref<SubTexture2D> m_GrassTexture, m_StoneTexture, m_GlassTexture;

		glm::vec2 m_ViewPortSize;

		glm::vec4 m_Color = { 1.f, 1.f, 1.f, 1.f };
		//Ref<Texure2D> m_Texture;
	};
}
