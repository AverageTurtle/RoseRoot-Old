#include "rrpch.h"
#include "Lua.h"
#include "RoseRoot/Renderer/Renderer2D.h"
namespace RoseRoot {

	//Lua Types
	struct Vec2 {
		float x = 0, y = 0;

		Vec2() {}
		Vec2(float lx,float ly)
			: x(lx),y(ly) {}
		~Vec2() {}
	};

	LuaScript::LuaScript(const std::string& filepath)
	{
		RR_PROFILE_FUNCTION();
		m_LuaState = sol::state();

		m_LuaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);

		//Register Functions
		m_LuaState.set_function("log", &BindRoseLog);
		m_LuaState.set_function("DrawSimpleQuad2D", &BindDrawQuad2DSimple);

		//Register Types
		m_LuaState.new_usertype<Vec2>("Vec2",
			"x", &Vec2::x,
			"y", &Vec2::y);

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
		const char* str = lua_tostring(ptrState, 1);
		RR_INFO(str);
		return 0;
	}

	int LuaScript::BindDrawQuad2DSimple(lua_State* ptrState)
	{
		const float x = lua_tonumber(ptrState, 1);
		const float y = lua_tonumber(ptrState, 2);

		const float sy = lua_tonumber(ptrState, 3);
		const float sx = lua_tonumber(ptrState, 4);

		const float r = lua_tonumber(ptrState, 5);
		const float g = lua_tonumber(ptrState, 6);
		const float b = lua_tonumber(ptrState, 7);
		const float a = lua_tonumber(ptrState, 8);

		Renderer2D::DrawQuad({ x, y }, { sy, sx }, { r, g, b, a });
		return 0;
	}

}