function LinkSpirvCross()
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
			"spirv-cross-cored.lib",
			"spirv-cross-glsld.lib",
			"spirv-cross-hlsld.lib",
			"SPIRV-Toolsd.lib"
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
			"spirv-cross-core.lib",
			"spirv-cross-glsl.lib",
			"spirv-cross-hlsl.lib",
			"SPIRV-Tools.lib"
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
			"spirv-cross-core.lib",
			"spirv-cross-glsl.lib",
			"spirv-cross-hlsl.lib",
			"SPIRV-Tools.lib"
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