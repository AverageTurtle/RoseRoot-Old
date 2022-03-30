#pragma once
#include <RoseRoot.h>

namespace Sandbox {
	class MainLayer : public RoseRoot::Layer {
	public:
		MainLayer();
		virtual ~MainLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(RoseRoot::Timestep ts) override;
		virtual void OnImGuiRender() override;
	private:
		//RoseRoot::LuaScript m_Lua = RoseRoot::LuaScript("assets/scripts/test.lua");
		//RoseRoot::LuaScript m_Lua2 = RoseRoot::LuaScript("assets/scripts/test2.lua");

		RoseRoot::EditorCamera m_EditorCamera;
	};
}