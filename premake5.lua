include "elysium_dependencies.lua"
include "vendor/imgui_suite/imgui_dependencies.lua"

project "Elysium"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	staticruntime "on"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "elysium_pch.h"
	pchsource "src/elysium_pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
	}

	includedirs
	{
		"src",
		
		"%{IncludeDir.glfw}",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.spirv_cross}",

		"%{ImGui_IncludeDir.ImGui}",
		"%{ImGui_IncludeDir.ImGuizmo}",
		"%{ImGui_IncludeDir.ImNodes}",
		"%{ImGui_IncludeDir.ImTextEditor}",
		
		"%{IncludeDir.entt}",
		"%{IncludeDir.IconFontCppHeaders}",
		"%{IncludeDir.stduuid}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.spd_log}"
	}
	
	libdirs
	{
	}
	
	links
	{
		"opengl32.lib",
		"GLFW",
		"ImGui",
		"ImGuizmo",
		"ImNodes",
		"ImTextEditor",
		"yaml-cpp",
	}

	LinkGLEW()
	LinkShaderc()
	LinkSpirvCross()

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PROJDIR=\'$(ProjectDir).\'",
			"SOLUDIR=\'$(SolutionDir).\'"
		}
		
		links
		{
			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}"
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
