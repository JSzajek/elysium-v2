#pragma once

#include "Elysium/Core/Memory.h"
#include "Elysium/Pipeline/Window.h"
#include "Elysium/Pipeline/LayerStack.h"
#include "Elysium/Events/ApplicationEvent.h"

#include "Elysium/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Elysium
{
	class Application
	{
	private:
		static Application* s_instance;
	private:
		Unique<Window> m_window;
		ImGuiLayer* m_imGuiLayer;
		bool m_running = true;
		bool m_minimized = false;
		LayerStack m_layerStack;
	public:
		Application(const std::string& name = "");
		Application(const std::string& name, const uint16_t width, const uint16_t height);

		virtual ~Application();

		void OnEvent(Event& _event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_instance; }
		inline Window& GetWindow() { return *m_window; }
	private:
		void Initialize(const WindowProperties& properties);
		void Run();
		bool OnWindowClose(WindowCloseEvent& _event);
		bool OnWindowResize(WindowResizeEvent& _event);
		friend int ::main(int argc, char** argv);
	};

	// To be defined in client
	Application* CreateApplication();
}