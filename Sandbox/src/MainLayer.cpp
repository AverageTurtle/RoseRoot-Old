#include "MainLayer.h"
#include "imgui/imgui.h"

//Temp draw cube
void DrawCube(glm::vec3 position, glm::vec4 color,VoxelEngine::Ref<VoxelEngine::SubTexture2D> texture)
{
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.f, 0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, color, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.f,-0.5f, 0.f) + position, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, color, texture, 1.f);
									
	VoxelEngine::RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, 0.5f) + position, { 1.f, 1.f, 1.f }, color, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuad(glm::vec3(0.f, 0.0f, -0.5f) + position, { 1.f, 1.f, 1.f }, color, texture, 1.f);
										
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, color, texture, 1.f);
	VoxelEngine::RendererVoxel::DrawQuadRotated(glm::vec3(-0.5f, 0.0f, 0.0f) + position, { 1.f, 1.f, 1.f }, { 0.f, 90.f, 0.f }, color, texture, 1.f);
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

	m_SpriteSheet = VoxelEngine::Texture2D::Create("assets/textures/SpriteSheet.png");
	m_ViewTest = VoxelEngine::Texture2D::Create("assets/textures/ViewTest.png");

	m_GrassTexture = VoxelEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 0 }, {16, 16});
	m_StoneTexture = VoxelEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 0 }, { 16, 16 });
	m_GlassTexture = VoxelEngine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 0 }, { 16, 16 });
}


void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(VoxelEngine::Timestep ts)
{
	VE_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);


	//Render
	VoxelEngine::RendererVoxel::ResetStats();

	const int size = 128;
	if (m_Scene == 1)
	{
		VoxelEngine::RenderCommand::SetClearColor({ 0.5, 0.6, 0.9, 1 });
		VoxelEngine::RenderCommand::Clear();

		VoxelEngine::RendererVoxel::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

		for (int z = 0; z < size; z++)
		{
			for (int x = 0; x < size; x++)
			{
				DrawCube({ x - (float)size/2, -2, z - (float)size / 2 }, m_Color,m_GrassTexture);
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

		//VoxelEngine::RendererVoxel::DrawQuad({ 0.f,0.f,-16.f }, { 16.f, 16.f, 0.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_GrassTexture, 16.f);

		VoxelEngine::RendererVoxel::EndScene();
	}
	else if (m_Scene == 2)
	{
		VoxelEngine::RenderCommand::SetClearColor({ 0.05, 0.05, 0.09, 1 });
		VoxelEngine::RenderCommand::Clear();
		VoxelEngine::RendererVoxel::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

		for (int z = 0; z < size; z++)
		{
			for (int x = 0; x < size; x++)
			{
				DrawCube({ x - (float)size / 2, -2, z - (float)size / 2 }, { m_Color.x/2, m_Color.y/2, m_Color.z/2, m_Color.a}, m_GrassTexture);
			}
		}
		DrawCube({ 4,  0, 0 }, { m_Color.x / 2, m_Color.y / 2, m_Color.z / 2, m_Color.a }, m_GlassTexture);
		DrawCube({ 4, -1, 0 }, { m_Color.x / 2, m_Color.y / 2, m_Color.z / 2, m_Color.a }, m_GlassTexture);

		//VoxelEngine::RendererVoxel::DrawQuad({ 0.f,0.f,-16.f }, { 16.f, 16.f, 0.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_GrassTexture, 16.f);

		VoxelEngine::RendererVoxel::EndScene();
	}
}

void MainLayer::OnImGuiRender()
{
	VE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::Text("Camera Fov: %.2f", m_CameraController.GetFOV());
	ImGui::Text("Camera Sensitivity: %.2f", m_CameraController.GetSensitivity());

	auto stats = VoxelEngine::RendererVoxel::GetStats();
	ImGui::Text("Renderer Voxel Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());

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
