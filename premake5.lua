include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Rose"
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
