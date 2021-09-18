#include <VoxelEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public VoxelEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_TAB))
			VE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(VoxelEngine::Event& event) override
	{
		if (event.GetEventType() == VoxelEngine::EventType::KeyPressed)
		{
			VoxelEngine::KeyPressedEvent& e = (VoxelEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == VE_KEY_TAB)
				VE_TRACE("Tab key is pressed (event)!");
			VE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public VoxelEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

VoxelEngine::Application* VoxelEngine::CreateApplication()
{
	return new Sandbox();
}