#include "rrpch.h"
#include "Lua.h"

namespace RoseRoot {
	LuaScript::LuaScript(const std::string& filepath)
	{
		RR_PROFILE_FUNCTION();
		m_LuaState = sol::state();

		m_LuaState.open_libraries(sol::lib::base, sol::lib::package);

		//Register Functions
		m_LuaState.set_function("log", &BindRoseLog);


		int resultL = luaL_loadfile(m_LuaState, filepath.c_str());
		//RR_CORE_ASSERT(resultL != LUA_OK, "Failed to load file!");
		resultL = lua_pcall(m_LuaState, 0, LUA_MULTRET, 0);
		//RR_CORE_ASSERT(resultL != LUA_OK, "LUA Script failed to run!!");


	}

	LuaScript::~LuaScript()
	{
		RR_PROFILE_FUNCTION();
		m_LuaState.end();
	}

	void LuaScript::Init()
	{
		RR_PROFILE_FUNCTION();
		if (lua_getglobal(m_LuaState, "Init") == LUA_TFUNCTION) {
			RR_CORE_ASSERT(lua_pcall(m_LuaState, 0, 0, 0) == LUA_OK, "Init did not return LUA_OKAY");
			lua_pop(m_LuaState, 1);
		}
		else
			RR_CORE_ASSERT("LUA Init global did not return a TFunction");
	}

	void LuaScript::Update(Timestep ts)
	{
		RR_PROFILE_FUNCTION();
		if (lua_getglobal(m_LuaState, "Update") == LUA_TFUNCTION) {
			lua_pushnumber(m_LuaState, ts);
			RR_CORE_ASSERT(lua_pcall(m_LuaState, 1, 0, 0) == LUA_OK, "Update did not return LUA_OKAY");
			lua_pop(m_LuaState, 1);
		}
		else
			RR_CORE_ASSERT("LUA Update global did not return a TFunction");
	}

	
	int LuaScript::BindRoseLog(lua_State* ptrState)
	{
		RR_PROFILE_FUNCTION();
		const char* str = lua_tostring(ptrState, 1);
		RR_INFO(str);
		return 0;
	}

}