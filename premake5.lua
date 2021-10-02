workspace "RoseRoot"
	architecture "x64"
	startproject "RoseStem"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "RoseRoot/vendor/GLFW/include"
IncludeDir["Glad"] = "RoseRoot/vendor/Glad/include"
IncludeDir["ImGui"] = "RoseRoot/vendor/imgui"
IncludeDir["glm"] = "RoseRoot/vendor/glm"
IncludeDir["stb_image"] = "RoseRoot/vendor/stb_image"
IncludeDir["entt"] = "RoseRoot/vendor/entt/include"

group "Dependencies"
	include "RoseRoot/vendor/GLFW"
	include "RoseRoot/vendor/Glad"
	include "RoseRoot/vendor/imgui"
group ""

project "RoseRoot"
	location "RoseRoot"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rrpch.h"
	pchsource "RoseRoot/src/rrpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RR_PLATFORM_WINDOWS",
			"RR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"RoseRoot/vendor/spdlog/include",
		"RoseRoot/src",
		"RoseRoot/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"RoseRoot"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RR_DIST"
		runtime "Release"
		optimize "on"


project "RoseStem"
	location "RoseStem"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"RoseRoot/vendor/spdlog/include",
		"RoseRoot/src",
		"RoseRoot/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"RoseRoot"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RR_DIST"
		runtime "Release"
		optimize "on"