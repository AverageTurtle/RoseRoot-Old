#pragma once
#include <VoxelEngine.h>

class MainLayer : public VoxelEngine::Layer
{
public:
	MainLayer();
	virtual ~MainLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(VoxelEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(VoxelEngine::Event& event) override;
private:
	VoxelEngine::FlightCameraController m_CameraController;

	VoxelEngine::Ref<VoxelEngine::Shader> m_Shader;
	VoxelEngine::Ref<VoxelEngine::VertexArray> m_VertexArray;

	VoxelEngine::Ref<VoxelEngine::Texure2D> m_Texture;
};