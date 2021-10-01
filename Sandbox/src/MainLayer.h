#pragma once
#include <RoseRoot.h>

#include "Core/Chunk.h"

class MainLayer : public RoseRoot::Layer
{
public:
	MainLayer(RoseRoot::Window& window);
	virtual ~MainLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(RoseRoot::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(RoseRoot::Event& event) override;

	bool KeyPressed(RoseRoot::KeyPressedEvent& e);
private:
	Chunk m_TestChunk;

	int m_Scene = 1;
	RoseRoot::FlightCameraController m_CameraController;

	RoseRoot::Window& m_Window;

	RoseRoot::Ref<RoseRoot::Shader> m_Shader;
	RoseRoot::Ref<RoseRoot::VertexArray> m_VertexArray;

	RoseRoot::Ref<RoseRoot::Texture2D> m_ViewTest;

	glm::vec4 m_Color = {1.f, 1.f, 1.f, 1.f};
	//VoxelEngine::Ref<VoxelEngine::Texure2D> m_Texture;
};