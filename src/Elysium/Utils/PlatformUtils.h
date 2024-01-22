#pragma once

#include <string>

namespace Elysium
{
	class FileDialogs
	{
	public:
		enum class DialogResult
		{
			Error,
			Yes,
			No,
			Cancel
		};
	public:
		// These return empty strings if canceled
		static std::string OpenFile(const char* filter);
		static std::string OpenDirectory();

		static std::string SaveFile(const char* filter);

		static DialogResult YesNoMessage(const char* title, const char* message);
		static DialogResult YesNoCancelMessage(const char* title, const char* message);
	};
}