function LinkGLEW()
	-- Get the location of the current script file
    local scriptLocation = debug.getinfo(1, "S").source:sub(2)

    -- Determine the relative directory based on the current script location
    local relativeDir = path.getdirectory(scriptLocation)

	includedirs
	{
		relativeDir .. "/include",
	}

	filter "configurations:Debug"
		links
		{
			"glew32d.lib"
		}
		libdirs
		{
			relativeDir .. "/Debug/lib"
		}
		postbuildcommands
		{
			"{COPY} " .. '"' .. relativeDir .. "/Debug/bin/" .. '"' .. " %{cfg.targetdir}"
		}

	filter "configurations:Release"
		links
		{
			"glew32.lib"
		}
		libdirs
		{
			relativeDir .. "/Release/lib"
		}
		postbuildcommands
		{
			"{COPY} " .. '"' .. relativeDir .. "/Release/bin/" .. '"' .. " %{cfg.targetdir}"
		}

	filter "configurations:Dist"
		links
		{
			"glew32.lib"
		}
		libdirs
		{
			relativeDir .. "/Release/lib"
		}
		postbuildcommands
		{
			"{COPY} " .. '"' .. relativeDir .. "/Release/bin/" .. '"' .. " %{cfg.targetdir}"
		}
end