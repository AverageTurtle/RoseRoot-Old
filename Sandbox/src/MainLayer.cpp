#include "MainLayer.h"
#include "imgui/imgui.h"

#include <chrono>


//Temp draw cube
void DrawCube(glm::vec3 position, VoxelEngine::Ref<VoxelEngine::Texture2D> texture)
{
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.f, 0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.f,-0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texture, 1.f);
									
	VoxelEngine::RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, 0.5f) + position, { 1.f, 1.f, 1.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, -0.5f) + position, { 1.f, 1.f, 1.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texture, 1.f);
										
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(-0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, texture, 1.f);
}

MainLayer::MainLayer(VoxelEngine::Window& window)
	: Layer("MainLayer"), m_Window(window), m_CameraController(16.f / 9.f)
{
}

void MainLayer::OnAttach()
{
	VE_PROFILE_FUNCTION();

	m_CameraController.SetTracking(false);
	m_Window.SetCapturesMouse(false);

	m_GrassTexture = VoxelEngine::Texture2D::Create("assets/textures/GrassBlockTop.png");
	m_StoneTexture = VoxelEngine::Texture2D::Create("assets/textures/Stone.png");
}


void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(VoxelEngine::Timestep ts)
{
	VE_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	//VoxelEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 }); //gray
	VoxelEngine::RenderCommand::SetClearColor({ 0.5, 0.6, 0.9, 1 });
	VoxelEngine::RenderCommand::Clear();

	VoxelEngine::RendererVoxel::BeginScene(m_CameraController.GetCamera());

	static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

	for (int z = 0; z < 8; z++)
	{
		for (int x = 0; x < 8; x++)
		{
			DrawCube({ x - 4, -2, z - 4 }, m_GrassTexture);
		}
	}
	DrawCube({ 0, -1, 0 }, m_StoneTexture);

	//VoxelEngine::RendererVoxel::DrawQuad({ 0.f,0.f,-16.f }, { 16.f, 16.f, 0.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_GrassTexture, 16.f);

	VoxelEngine::RendererVoxel::EndScene();

}

void MainLayer::OnImGuiRender()
{
	VE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::Text("Fov: %.2f", m_CameraController.GetFOV());
	ImGui::ColorEdit4("Object Color:", glm::value_ptr(m_Color));

	ImGui::End();
}

void MainLayer::OnEvent(VoxelEngine::Event& event)
{
	m_CameraController.OnEvent(event);

	VoxelEngine::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<VoxelEngine::KeyPressedEvent>(VE_BIND_EVENT_FN(MainLayer::KeyPressed));
}
bool MainLayer::KeyPressed(VoxelEngine::KeyPressedEvent& e)
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

	return false;
}
