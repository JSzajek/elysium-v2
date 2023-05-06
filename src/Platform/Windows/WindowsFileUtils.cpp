#include "elysium_pch.h"

#include "Elysium/Core/Macros.h"
#include "Elysium/Utils/FileUtils.h"

#include <sys/stat.h>
#include <sys/types.h>

#include <stack>
#include <algorithm>

namespace Elysium
{
	bool FileUtils::FileExists(const std::string& filepath, std::filesystem::path& path)
	{
		path = std::filesystem::path(filepath);
		std::filesystem::file_status s = std::filesystem::file_status{};
		return std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(path);
	}

	bool FileUtils::FileExists(const std::filesystem::path& filepath)
	{
		std::filesystem::file_status s = std::filesystem::file_status{};
		return std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(filepath);
	}

	std::string FileUtils::GetFileName(const std::filesystem::path& path, bool extension)
	{
		if (extension)
			return path.filename().generic_string();
		else
			return path.stem().generic_string();
	}

	int64_t FileUtils::LastModifiedTime(const std::string& filepath)
	{
		struct _stat result;
		if (_stat(filepath.c_str(), &result) == 0)
		{
			return result.st_mtime;
		}
		return 0;
	}

	std::filesystem::path FileUtils::GetCurrentProjectDir()
	{
		std::string dir = ELYSIUM_EXPAND_MACRO_STRING(PROJDIR);
		dir.erase(std::remove(dir.begin(), dir.end(), '\''), dir.end());

		return std::filesystem::path(dir.substr(0, dir.length() - 1));
	}

	std::filesystem::path FileUtils::GetCurrentSolutionDir()
	{
		std::string dir = ELYSIUM_EXPAND_MACRO_STRING(SOLUDIR);
		dir.erase(std::remove(dir.begin(), dir.end(), '\''), dir.end());

		return std::filesystem::path(dir.substr(0, dir.length() - 1));
	}

	std::filesystem::path FileUtils::GetAssetPath(const std::filesystem::path& path)
	{
		std::stack<std::filesystem::path> checkDirectories;

		checkDirectories.push(GetCurrentProjectDir());
		checkDirectories.push(GetCurrentSolutionDir());
		checkDirectories.push("");

		while (!checkDirectories.empty())
		{
			const std::filesystem::path potentialFileDir = checkDirectories.top() / path;
			if (FileExists(potentialFileDir))
				return potentialFileDir;

			checkDirectories.pop();
		}
		ELYSIUM_CORE_ERROR("[Core]: Couldn't Find Asset {0}", path.generic_string());
		return path;
	}

	std::string FileUtils::GetAssetPath_Str(const std::filesystem::path& path)
	{
		return GetAssetPath(path).generic_string();
	}
}