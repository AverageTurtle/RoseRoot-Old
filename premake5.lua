workspace "VoxelEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "VoxelEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "VoxelEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "VoxelEngine/vendor/imgui"
IncludeDir["glm"] = "VoxelEngine/vendor/glm"

include "VoxelEngine/vendor/GLFW"
include "VoxelEngine/vendor/Glad"
include "VoxelEngine/vendor/imgui"

project "VoxelEngine"
	location "VoxelEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vepch.h"
	pchsource "VoxelEngine/src/vepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
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
		"%{IncludeDir.glm}"
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
			"VE_PLATFORM_WINDOWS",
			"VE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "VE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VE_DIST"
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
		"VoxelEngine/vendor/spdlog/include",
		"VoxelEngine/src",
		"VoxelEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"VoxelEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VE_DIST"
		runtime "Release"
		optimize "on"