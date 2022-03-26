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
		RR_CORE_ASSERT(resultL == LUA_OK, "Failed to load file!");
		resultL = lua_pcall(m_LuaState, 0, LUA_MULTRET, 0);
		RR_CORE_ASSERT(resultL == LUA_OK, "LUA Script failed to run!!");
	}

	LuaScript::~LuaScript()
	{
		RR_PROFILE_FUNCTION();
		m_LuaState.end();
	}
	void LuaScript::Init()
	{
		RR_PROFILE_FUNCTION();
		sol::function Init = m_LuaState["Init"];
		Init();
	}

	void LuaScript::Update(Timestep ts)
	{
		RR_PROFILE_FUNCTION();
		sol::function Update = m_LuaState["Update"];
		Update((float)ts);
	}

	
	int LuaScript::BindRoseLog(lua_State* ptrState)
	{
		RR_PROFILE_FUNCTION();
		const char* str = lua_tostring(ptrState, 1);
		RR_INFO(str);
		return 0;
	}

}