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
		//VE_INFO("ExampleLayer::Update");

		if (VoxelEngine::Input::IsKeyPressed(VE_KEY_W))
			VE_TRACE("W is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(VoxelEngine::Event& event) override
	{
		//VE_TRACE("{0}", event);
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