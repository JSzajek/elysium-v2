#include "elysium_pch.h"
#include "Elysium/Utils/PlatformUtils.h"

#include "Elysium/Pipeline/Application.h"

#include <ShlObj.h>
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

	std::string FileDialogs::OpenDirectory()
	{
		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		// Create the File Open dialog
		IFileOpenDialog* pFileOpenDialog;
		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpenDialog));

		if (SUCCEEDED(hr)) 
		{
			// Set options to allow the selection of folders
			DWORD dwOptions;
			pFileOpenDialog->GetOptions(&dwOptions);
			pFileOpenDialog->SetOptions(dwOptions | FOS_PICKFOLDERS);

			// Show the dialog
			hr = pFileOpenDialog->Show(NULL);

			if (SUCCEEDED(hr)) 
			{
				// Get the selected folder
				IShellItem* pItem;
				hr = pFileOpenDialog->GetResult(&pItem);

				if (SUCCEEDED(hr)) 
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) 
					{
						// Get the required buffer size
						int bufferSize = WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, NULL, 0, NULL, NULL);

						// Allocate a buffer for the converted string
						std::string result(bufferSize, 0);

						// Convert the wide string to multibyte (UTF-8) string
						WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, &result[0], bufferSize, NULL, NULL);

						// Free the memory
						CoTaskMemFree(pszFilePath);
						pItem->Release();
						pFileOpenDialog->Release();
						CoUninitialize();

						return result;
					}
					pItem->Release();
				}
			}
			pFileOpenDialog->Release();
		}
		CoUninitialize();
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