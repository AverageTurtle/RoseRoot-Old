#include "MainLayer.h"

namespace Sandbox {
	MainLayer::MainLayer()
		: Layer("MainLayer")
	{

	}
	void MainLayer::OnAttach()
	{
		
		m_Lua.Init();
	}
	void MainLayer::OnDetach()
	{
	}
	void MainLayer::OnUpdate(RoseRoot::Timestep ts)
	{
		m_Lua.Update(ts);

		RoseRoot::RenderCommand::SetClearColor({0.2, 0.0, 0.2, 1.0});
		RoseRoot::RenderCommand::Clear();
		


	}
	void MainLayer::OnImGuiRender()
	{
	}
}


