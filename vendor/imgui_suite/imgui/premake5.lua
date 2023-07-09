include "Elysium/elysium_dependencies.lua"

project "ImGui"
	kind "StaticLib"
	language "C++"

	staticruntime "on"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_impl_opengl3.h",
		"imgui_impl_opengl3.cpp",
		"imgui_impl_glfw.h",
		"imgui_impl_glfw.cpp",
		"imgui_demo.cpp"
	}

	includedirs
	{
		"%{IncludeDir.glfw}"
	}

	links
	{
		"GLFW"
	}

	LinkGLEW()

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		runtime "Release"
		optimize "on"