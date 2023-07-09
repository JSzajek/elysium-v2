include "vendor/glew/glewlink.lua"
include "vendor/shaderc/shaderclink.lua"
include "vendor/spirv_cross/spirvcrosslink.lua"

-- Elysium Dependencies

IncludeDir = {}
IncludeDir["entt"] = "%{wks.location}/Elysium/vendor/entt"
IncludeDir["IconFontCppHeaders"] = "%{wks.location}/Elysium/vendor/iconfontcppheaders"
IncludeDir["stduuid"] = "%{wks.location}/Elysium/vendor/stduuid"
IncludeDir["stb_image"] = "%{wks.location}/Elysium/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Elysium/vendor/yaml-cpp/include"
IncludeDir["spd_log"] = "%{wks.location}/Elysium/vendor/spdlog/include"
IncludeDir["glew"] = "%{wks.location}/Elysium/vendor/glew/include"
IncludeDir["glfw"] = "%{wks.location}/Elysium/vendor/glfw/include"
IncludeDir["spirv_cross"] = "%{wks.location}/Elysium/vendor/spirv_cross/include"
IncludeDir["shaderc"] = "%{wks.location}/Elysium/vendor/shaderc/include"

Library = {}

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"