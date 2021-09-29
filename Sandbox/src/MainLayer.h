#pragma once
#include <VoxelEngine.h>

class MainLayer : public VoxelEngine::Layer
{
public:
	MainLayer(VoxelEngine::Window& window);
	virtual ~MainLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(VoxelEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(VoxelEngine::Event& event) override;

	bool KeyPressed(VoxelEngine::KeyPressedEvent& e);
private:
	int m_Scene = 1;
	VoxelEngine::FlightCameraController m_CameraController;

	VoxelEngine::Window& m_Window;

	VoxelEngine::Ref<VoxelEngine::Shader> m_Shader;
	VoxelEngine::Ref<VoxelEngine::VertexArray> m_VertexArray;

	VoxelEngine::Ref<VoxelEngine::Texture2D> m_SpriteSheet, m_ViewTest;
	VoxelEngine::Ref<VoxelEngine::SubTexture2D> m_GrassTexture, m_StoneTexture, m_GlassTexture;

	glm::vec4 m_Color = {1.f, 1.f, 1.f, 1.f};
	//VoxelEngine::Ref<VoxelEngine::Texure2D> m_Texture;
};