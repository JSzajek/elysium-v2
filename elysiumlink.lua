include "Elysium/elysium_dependencies.lua"

function LinkElysium()
	-- Get the location of the current script file
    local scriptLocation = debug.getinfo(1, "S").source:sub(2)

    -- Determine the relative directory based on the current script location
    local relativeDir = path.getdirectory(scriptLocation)

    includedirs
	{
		relativeDir .. "/src",
	}
	
	links
	{
		"Elysium"
	}

	postbuildcommands
	{
		"{COPY} " .. '"' .. "%{cfg.targetdir}/../" .. "Elysium/*.dll" .. '"' .. " %{cfg.targetdir}",
		"{COPY} " .. '"' .. "%{cfg.targetdir}/../" .. "Elysium/*.pdb" .. '"' .. " %{cfg.targetdir}"
	}
end