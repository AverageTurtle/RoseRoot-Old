#pragma once
#include "RoseRoot/Core/Timestep.h"
#include <sol.hpp>

namespace RoseRoot {

	class LuaScript {
	public:
		LuaScript(const std::string& filepath);
		~LuaScript();

		void Init();
		void Update(Timestep ts);
	private:
		static int BindRoseLog(lua_State* ptrState);
	private:
		sol::state m_LuaState;

		
	};
}