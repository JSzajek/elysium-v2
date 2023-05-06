project "Elysium"
	location "Elysium"
	kind "StaticLib"

	language "C++"
	cppdialect "C++17"
	
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "elysium_pch.h"
	pchsource "src/elysium_pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		"vendor/imgui/**",
		"vendor/imguizmo/**",
		"vendor/imnodes/**",
	}

	includedirs
	{
		"src",

		"vendor/stb_image",

		"vendor/imgui",
		"vendor/imguizmo",
		"vendor/imnodes",
		"vendor/iconfontcppheaders",

		"vendor/entt",
		"vendor/stduuid",
	}
	
	libdirs
	{
	}
	
	links
	{
		"glew",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PROJDIR=\'$(ProjectDir).\'",
			"SOLUDIR=\'$(SolutionDir).\'"
		}

	filter "configurations:Debug"
		defines "ELYSIUM_DEBUG"
		symbols "on"
	filter "configurations:Release"
		defines "ELYSIUM_RELEASE"
		optimize "on"
	filter "configurations:Dist"
		defines "ELYSIUM_DIST"
		optimize "Full"

project "NormalsRotator"
	location "NormalsRotator"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"

	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "norm_pch.h"
	pchsource "%{prj.name}/src/norm_pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",

		"Elysium/src",
		"Elysium/vendor/imgui",
		"Elysium/vendor/imguizmo",
		"Elysium/vendor/imnodes",
		"Elysium/vendor/iconfontcppheaders",

		"Elysium/vendor/entt",
		"Elysium/vendor/stduuid",
	}
	
	libdirs
	{
	}

	links
	{
		"Elysium",
	}

	postbuildcommands {
		"{COPY} Content/ %{cfg.targetdir}/Content/"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PROJDIR=\'$(ProjectDir).\'",
			"SOLUDIR=\'$(SolutionDir).\'"
		}

	filter "configurations:Debug"
		defines "ELYSIUM_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "ELYSIUM_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "ELYSIUM_DIST"
		optimize "Full"
