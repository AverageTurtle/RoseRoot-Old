#pragma once
#include <VoxelEngine.h>
//---Entry Point---
#include <VoxelEngine/Core/EntryPoint.h>
//-----------------

#include "MainLayer.h"

class Sandbox : public VoxelEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new MainLayer(GetWindow()));
	}

	~Sandbox()
	{

	}
};

VoxelEngine::Application* VoxelEngine::CreateApplication()
{
	return new Sandbox();
}