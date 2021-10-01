#include "MainLayer.h"
#include "imgui/imgui.h"

MainLayer::MainLayer(RoseRoot::Window& window)
	: Layer("MainLayer"), m_Window(window), m_CameraController(16.f / 9.f), m_TestChunk()
{
}

void MainLayer::OnAttach()
{
	RR_PROFILE_FUNCTION();

	m_CameraController.SetTracking(false);
	m_Window.SetCapturesMouse(false);

	m_ViewTest = RoseRoot::Texture2D::Create("assets/textures/ViewTest.png");

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				m_TestChunk.SetBlock(x, y, z, BlockType::Stone);
			}
		}
	}
	m_TestChunk.RegenAllMeshes();
}


void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(RoseRoot::Timestep ts)
{
	RR_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);


	//Render
	RoseRoot::RendererVoxel::ResetStats();

	RoseRoot::RenderCommand::SetClearColor({ 0.5, 0.6, 0.9, 1 });
	RoseRoot::RenderCommand::Clear();

	RoseRoot::RendererVoxel::BeginScene(m_CameraController.GetCamera());

	RoseRoot::RendererVoxel::DrawQuad({ 1,0,1 }, { 1,1,1 }, { 1,1,1,1 });
	m_TestChunk.RegenAllMeshes();
	m_TestChunk.Draw();

	RoseRoot::RendererVoxel::EndScene();
}

void MainLayer::OnImGuiRender()
{
	RR_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::Text("Camera Fov: %.2f", m_CameraController.GetFOV());
	ImGui::Text("Camera Sensitivity: %.2f", m_CameraController.GetSensitivity());

	auto stats = RoseRoot::RendererVoxel::GetStats();
	ImGui::Text("Renderer Voxel Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Object Color:", glm::value_ptr(m_Color));

	ImGui::End();
}

void MainLayer::OnEvent(RoseRoot::Event& event)
{
	m_CameraController.OnEvent(event);

	RoseRoot::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<RoseRoot::KeyPressedEvent>(RR_BIND_EVENT_FN(MainLayer::KeyPressed));
}
bool MainLayer::KeyPressed(RoseRoot::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == RR_KEY_ESCAPE)
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

	if (e.GetKeyCode() == RR_KEY_I)
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
