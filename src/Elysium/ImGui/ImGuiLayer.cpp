#include "elysium_pch.h"

#include "Elysium/ImGui/ImGuiLayer.h"

#include "Elysium/Core/Macros.h"
#include "Elysium/Core/KeyCodes.h"
#include "Elysium/Pipeline/Application.h"
#include "Elysium/Utils/FileUtils.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <imnodes.h>

#include <IconsFontAwesome5.h>

// TODO:: Move usage into static render call - Currently Temporary
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

namespace Elysium
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"), m_blockEvents(false)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		//ELYSIUM_PROFILE_FUNCTION();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImNodes::CreateContext();

		ImGui::StyleColorsDark();

		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		//// Font From File
		float fontSize = 18.0f;
		io.Fonts->AddFontFromFileTTF(FileUtils::GetAssetPath_Str("Content/Engine/fonts/opensans/OpenSans-Bold.ttf").c_str(), fontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(FileUtils::GetAssetPath_Str("Content/Engine/fonts/opensans/OpenSans-Regular.ttf").c_str(), fontSize);
		//io.Fonts->AddFontFromFileTTF("../Elysium/.default_assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
		//io.FontDefault = io.Fonts->AddFontFromFileTTF("../Elysium/.default_assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);

		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		//io.Fonts->AddFontFromFileTTF("assets/fonts/IconFontCppHeaders/fa-regular-400.ttf", 13.0f, &config, icon_ranges);
		io.Fonts->AddFontFromFileTTF(FileUtils::GetAssetPath_Str("Content/Engine/fonts/IconFontCppHeaders/fa-solid-900.ttf").c_str(), 13.0f, &config, icon_ranges);
		io.Fonts->AddFontFromFileTTF(FileUtils::GetAssetPath_Str("Content/Engine/fonts/IconFontCppHeaders/fa-brands-400.ttf").c_str(), 13.0f, &config, icon_ranges);
		//io.Fonts->AddFontFromFileTTF("../Elysium/.default_assets/fonts/IconFontCppHeaders/fa-solid-900.ttf", 13.0f, &config, icon_ranges);
		//io.Fonts->AddFontFromFileTTF("../Elysium/.default_assets/fonts/IconFontCppHeaders/fa-brands-400.ttf", 13.0f, &config, icon_ranges);

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		auto& window = Application::Get().GetWindow();
		io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));

		// Set ImNodes IO Modifiers
		ImNodesIO& nodeio = ImNodes::GetIO();
		ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
		nodeio.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window.GetNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiLayer::OnDetach()
	{
		//ELYSIUM_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		ImNodes::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& _event)
	{
		if (m_blockEvents)
		{
			auto& io = ImGui::GetIO();
			_event.Handled |= _event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			_event.Handled |= _event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		//ELYSIUM_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void ImGuiLayer::End()
	{
		//ELYSIUM_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}