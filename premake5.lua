include "./vendor/premake/premake_customization/solution_items.lua"

workspace "RoseRoot"
	architecture "x86_64"
	startproject "RoseStem"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/RoseRoot/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/RoseRoot/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/RoseRoot/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/RoseRoot/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/RoseRoot/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/RoseRoot/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/RoseRoot/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/RoseRoot/vendor/imguizmo"

group "Dependencies"
	include "vendor/premake"
	include "RoseRoot/vendor/GLFW"
	include "RoseRoot/vendor/Glad"
	include "RoseRoot/vendor/imgui"
	include "RoseRoot/vendor/yaml-cpp"
group ""

include "RoseRoot"
include "Sandbox"
include "RoseStem"
