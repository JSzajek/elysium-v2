#include "elysium_pch.h"
#include "Elysium/Utils/StringUtils.h"

namespace Elysium
{
	constexpr unsigned int StringUtils::StringToInt(const char* str, int h)
	{
		return !str[h] ? 5381 : (StringToInt(str, h + 1) * 33) ^ str[h];
	}

	std::string StringUtils::ExtractFileName(const std::string& filepath, bool removeExtension)
	{
		auto result = filepath;

		const size_t last_slash_idx = result.find_last_of("\\/");
		if (std::string::npos != last_slash_idx)
			result.erase(0, last_slash_idx + 1);

		if (!removeExtension)
			return result;

		// Remove extension if present.
		const size_t period_idx = result.rfind('.');
		if (period_idx > last_slash_idx && std::string::npos != period_idx)
			result.erase(period_idx);
		return result;
	}
}