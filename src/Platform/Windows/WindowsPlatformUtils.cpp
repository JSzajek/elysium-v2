#include "elysium_pch.h"
#include "Elysium/Utils/PlatformUtils.h"

#include "Elysium/Pipeline/Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Elysium
{
	std::string FileDialogs::OpenFile(const char* filter)
	{
		OPENFILENAMEA openfilename;
		CHAR szFile[260] = { 0 };
		CHAR currentDirectory[256] = { 0 };

		ZeroMemory(&openfilename, sizeof(OPENFILENAME));
		openfilename.lStructSize = sizeof(OPENFILENAME);
		openfilename.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		openfilename.lpstrFile = szFile;
		openfilename.nMaxFile = sizeof(szFile);

		if (GetCurrentDirectoryA(256, currentDirectory))
		{
			openfilename.lpstrInitialDir = currentDirectory;
		}

		openfilename.lpstrFilter = filter;
		openfilename.nFilterIndex = 1;
		openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&openfilename) == TRUE)
		{
			return openfilename.lpstrFile;
		}
		return "";
	}

	std::string FileDialogs::SaveFile(const char* filter)
	{
		OPENFILENAMEA openfilename;
		CHAR szFile[260] = { 0 };
		CHAR currentDirectory[256] = { 0 };

		ZeroMemory(&openfilename, sizeof(OPENFILENAME));
		openfilename.lStructSize = sizeof(OPENFILENAME);
		openfilename.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		openfilename.lpstrFile = szFile;
		openfilename.nMaxFile = sizeof(szFile);

		if (GetCurrentDirectoryA(256, currentDirectory))
		{
			openfilename.lpstrInitialDir = currentDirectory;
		}

		openfilename.lpstrFilter = filter;
		openfilename.nFilterIndex = 1;
		openfilename.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		openfilename.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&openfilename) == TRUE)
		{
			return openfilename.lpstrFile;
		}
		return "";
	}

	FileDialogs::DialogResult FileDialogs::YesNoMessage(const char* title, const char* message)
	{
		HWND window = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		int result = MessageBoxA(window, message, title, MB_YESNO);

		switch (result)
		{
		case IDYES:
			return FileDialogs::DialogResult::Yes;
		case IDNO:
			return FileDialogs::DialogResult::No;
		default:
			return FileDialogs::DialogResult::Error;
		}
	}

	FileDialogs::DialogResult FileDialogs::YesNoCancelMessage(const char* title, const char* message)
	{
		HWND window = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		int result = MessageBoxA(window, message, title, MB_YESNOCANCEL);

		switch (result)
		{
		case IDYES:
			return FileDialogs::DialogResult::Yes;
		case IDNO:
			return FileDialogs::DialogResult::No;
		case IDCANCEL:
			return FileDialogs::DialogResult::Cancel;
		default:
			return FileDialogs::DialogResult::Error;
		}
	}
}