#pragma once

#include "Core.h"

#include "Window.h"
#include "VoxelEngine/Core/LayerStack.h"
#include "VoxelEngine/Events/Event.h"
#include "VoxelEngine/Events/ApplicationEvent.h"

#include "VoxelEngine/Core/Timestep.h"

#include "VoxelEngine/ImGui/ImGuiLayer.h"

namespace VoxelEngine {

	class VOXELENGINE_API Application
	{
	public:
		Application(const std::string& name = "VoxelEngine Application");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window;  }

		void Close() { m_Running = false; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance;  }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}