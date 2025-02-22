#pragma once

#include "Elysium/Logging/Instrumentor.h"
#include "Elysium/Pipeline/Application.h"

#ifdef ELYSIUM_PLATFORM_WINDOWS

#if ELYSIUM_RELEASE
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

extern Elysium::Application* Elysium::CreateApplication();

/// <summary>
/// The main application entry point.
/// </summary>
/// <param name="argc">The number of argument parameters</param>
/// <param name="argv">The passed arguments</param>
/// <returns>The application state</returns>
int main(int argc, char** argv)
{
	Elysium::Log::Init();

	ELYSIUM_PROFILE_BEGIN_SESSION("Startup", "ElysiumProfile_Startup.json");
	auto app = Elysium::CreateApplication();
	ELYSIUM_PROFILE_END_SESSION();

	ELYSIUM_PROFILE_BEGIN_SESSION("Runtime", "ElysiumProfile_Runtime.json");
	app->Run();
	ELYSIUM_PROFILE_END_SESSION();
	
	ELYSIUM_PROFILE_BEGIN_SESSION("Shutdown", "ElysiumProfile_Shutdown.json");
	delete app;
	ELYSIUM_PROFILE_END_SESSION();
}

#endif