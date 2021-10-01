#pragma once
#include <RoseRoot.h>
//---Entry Point---
#include <RoseRoot/Core/EntryPoint.h>
//-----------------

#include "MainLayer.h"

class Sandbox : public RoseRoot::Application
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

RoseRoot::Application* RoseRoot::CreateApplication()
{
	return new Sandbox();
}