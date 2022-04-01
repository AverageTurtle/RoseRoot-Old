#pragma once
#include "RoseRoot/Core/Timestep.h"
#include "RoseRoot/Scene/Entity.h"
#include "LuaTypes.h"

#define SOL_ALL_SAFETIES_ON
#include <sol.hpp>

namespace RoseRoot {
	
	class LuaScript {
	public:
		LuaScript(Entity entity,const std::string& filepath);
		~LuaScript();

		void Init();
		void Update(Timestep ts);

		
	private:
		static int BindRoseLog(lua_State* ptrState);
	private:
		Ref<LuaEntity> m_LuaEntity;
		sol::state m_LuaState;
	};


}