#pragma once

#include "elysium_pch.h"

#include "Elysium/Core/Base.h"
#include "Elysium/Events/Event.h"

namespace Elysium
{
	struct WindowProperties
	{
	public:
		std::string Title;
		unsigned int Width;
		unsigned int Height;
	public:
		WindowProperties(const std::string& title = "ELYSIUM Project", unsigned int width = 960, unsigned int height = 540)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
	public:
		virtual ~Window() { };
	public:
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual double GetCurrentUpTime() const = 0;

		virtual void* GetNativeWindow() const = 0;
	public:
		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}