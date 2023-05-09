-- Elysium Dependencies

IncludeDir = {}
IncludeDir["entt"] = "%{wks.location}/Elysium/vendor/entt"
IncludeDir["IconFontCppHeaders"] = "%{wks.location}/Elysium/vendor/iconfontcppheaders"
IncludeDir["stduuid"] = "%{wks.location}/Elysium/vendor/stduuid"
IncludeDir["stb_image"] = "%{wks.location}/Elysium/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Elysium/vendor/yaml-cpp/include"

Library = {}

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"