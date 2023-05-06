#pragma once

#include <filesystem>

namespace Elysium
{
	class FileUtils
	{
	public:
		static bool FileExists(const std::string& filepath, std::filesystem::path& path);
		static bool FileExists(const std::filesystem::path& filepath);

		static std::string GetFileName(const std::filesystem::path& path, bool extension = false);

		static int64_t LastModifiedTime(const std::string& filepath);

		static std::filesystem::path GetCurrentProjectDir();
		static std::filesystem::path GetCurrentSolutionDir();

		static std::filesystem::path GetAssetPath(const std::filesystem::path& path);
		static std::string GetAssetPath_Str(const std::filesystem::path& path);
	};
}