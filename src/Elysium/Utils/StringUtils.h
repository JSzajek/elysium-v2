#pragma once

#include <string>

namespace Elysium
{
	class StringUtils
	{
	public:
		static constexpr unsigned int StringToInt(const char* str, int h = 0);
		static std::string ExtractFileName(const std::string& filepath, bool removeExtension = true);

		static constexpr inline uint32_t StrHash(const std::string_view& str) noexcept
		{
			uint32_t hash = 5381;
			for (auto iter = str.begin(); iter < str.end(); ++iter)
				hash = ((hash << 5) + hash) + (unsigned char)*iter;
			return hash;
		}
	};

	constexpr inline unsigned int operator ""_(char const* p, size_t) { return StringUtils::StrHash(p); }
}