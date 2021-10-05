project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/RoseRoot/vendor/spdlog/include",
		"%{wks.location}/RoseRoot/src",
		"%{wks.location}/RoseRoot/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"RoseRoot"
	}

	filter "system:windows"
		systemversion "latest"

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