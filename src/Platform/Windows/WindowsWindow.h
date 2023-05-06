#pragma once

#include "Elysium/Pipeline/Window.h"
#include "Elysium/Graphics/GraphicsContext.h"

#include <memory>

struct GLFWwindow;

namespace Elysium
{
	class WindowsWindow : public Window
	{
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual unsigned int GetWidth() const override { return m_data.Width; }
		virtual unsigned int GetHeight() const override { return m_data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; };
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual double GetCurrentUpTime() const override;

		virtual inline void* GetNativeWindow() const override { return m_window; }
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void ShutDown();
	private:
		WindowData m_data;
		GLFWwindow* m_window;
		std::unique_ptr<GraphicsContext> m_context;
	};
}