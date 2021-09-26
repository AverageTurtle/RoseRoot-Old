#include "MainLayer.h"
#include "imgui/imgui.h"

#include <chrono>

template <typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({m_Name, duration});
	}
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

MainLayer::MainLayer(VoxelEngine::Window& window)
	: Layer("MainLayer"), m_Window(window), m_CameraController(16.f / 9.f)
{
}

void MainLayer::OnAttach()
{
	m_Window.SetCapturesMouse(true);
	m_GrassTexture = VoxelEngine::Texure2D::Create("assets/textures/GrassBlockTop.png");
}


void MainLayer::OnDetach()
{
}

void MainLayer::OnUpdate(VoxelEngine::Timestep ts)
{
	PROFILE_SCOPE("MainLayer::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("Renderer Prep");
		VoxelEngine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		VoxelEngine::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		VoxelEngine::RendererVoxel::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f));

		VoxelEngine::RendererVoxel::DrawQuad({ 0.f, 0.f,0.f }, { 1.f, 1.f, 1.f }, { 90.f, 0.f, 0.f }, m_Color);
		VoxelEngine::RendererVoxel::DrawQuad({ 0.f,-1.f,0.f }, { 16.f, 1.f, 16.f }, { 90.f, 0.f, 0.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_GrassTexture);

		VoxelEngine::Renderer::EndScene();
	}
}

void MainLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Fov: %.2f", m_CameraController.GetFOV());
	ImGui::ColorEdit4("Object Color:", glm::value_ptr(m_Color));

	for (auto& result : m_ProfileResults)
	{
		char label [50] ;
		strcpy(label, result.Name);
		strcat(label, "%.3fms");
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

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
