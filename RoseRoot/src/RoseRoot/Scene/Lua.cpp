#include "rrpch.h"
#include "Lua.h"
#include "RoseRoot/Renderer/Renderer2D.h"
namespace RoseRoot {

	//Lua Types
	struct Vec2 {
		float x = 0, y = 0;

		Vec2() {}
		Vec2(float lx, float ly)
			: x(lx), y(ly) {}
		~Vec2() {}
	};
	struct Color {
		float r = 0, g = 0, b = 0, a = 1;

		Color() {}
		Color(float r, float g, float b, float a)
			: r(r), g(g), b(b), a(a) {}
		~Color() {}

		
	};	
	Color CreateColor(float r, float g, float b, float a)
	{return Color(r, g, b, a);}

	static void DrawQuadSimple(Vec2 pos, Vec2 size, Color color)
	{
		Renderer2D::DrawQuad({ pos.x, pos.y }, { size.x, size.y }, { color.r, color.g, color.b, color.a });
	}

	LuaScript::LuaScript(const std::string& filepath)
	{
		RR_PROFILE_FUNCTION();
		m_LuaState = sol::state();

		m_LuaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);

		//Register Types
		m_LuaState.new_usertype<Vec2>("Vec2",
			"x", &Vec2::x,
			"y", &Vec2::y);

		m_LuaState.new_usertype<Color>("Color",
			"r", &Color::r,
			"g", &Color::g,
			"b", &Color::b,
			"a", &Color::a);

		//Register Util/Core Functions
		m_LuaState.set_function("log", &BindRoseLog);

		//Render2D lua Binding
		auto renderer2D = m_LuaState["Renderer2D"].get_or_create<sol::table>();
		renderer2D.set_function("DrawSimpleQuad", &DrawQuadSimple);

		
		m_LuaState.set_function("CreateColor", &CreateColor);

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



}