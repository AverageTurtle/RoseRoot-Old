#pragma once

#include "Core.h"

#include "Window.h"
#include "VoxelEngine/LayerStack.h"
#include "Events/Event.h"
#include "VoxelEngine/Events/ApplicationEvent.h"

#include "VoxelEngine/ImGui/ImGuiLayer.h"

namespace VoxelEngine {

	class VOXELENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance;  }
		inline Window& GetWindow() { return *m_Window;  }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}