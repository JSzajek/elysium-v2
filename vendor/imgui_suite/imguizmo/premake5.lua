include "../imgui_dependencies.lua"

project "ImGuizmo"
	kind "StaticLib"
	language "C++"

	staticruntime "on"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ImGuizmo.h",
		"ImGuizmo.cpp",
		"ImSequencer.h",
		"ImSequencer.cpp",
		"ImGradient.cpp",
		"ImGradient.h",
		"ImCurveEdit.h",
		"ImCurveEdit.cpp"
	}

	includedirs
	{
		"%{ImGui_IncludeDir.ImGui}",
	}

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