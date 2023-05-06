#include "elysium_pch.h"

#include "WindowsWindow.h"

#include "Elysium/Events/ApplicationEvent.h"
#include "Elysium/Events/KeyEvent.h"
#include "Elysium/Events/MouseEvent.h"

#include "Elysium/Logging/Log.h"
#include "Elysium/Core/Asserts.h"

#include <GLFW/glfw3.h>

namespace Elysium
{
	static bool GLFWInitialized = false;
	static bool GLEWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ELYSIUM_CORE_ERROR("GLFW ERROR: [{0}]: {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		m_data.Title = properties.Title;
		m_data.Width = properties.Width;
		m_data.Height = properties.Height;

		ELYSIUM_CORE_INFO("Intializing Window {0} ({1}, {2})", m_data.Title, m_data.Width, m_data.Height);

		if (!GLFWInitialized)
		{
			int success = glfwInit();
			ELYSIUM_CORE_ASSERT(success, "GLFW Couldn't initialize.");

			glfwSetErrorCallback(GLFWErrorCallback);

			GLFWInitialized = true;
		}

		// Force usage of OpenGL 4.2.0
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow((int)properties.Width, (int)properties.Height, properties.Title.c_str(), NULL, NULL);
		glfwSetWindowUserPointer(m_window, &m_data);

		m_context = GraphicsContext::Create(m_window);
		m_context->Init();

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = static_cast<unsigned int>(width);
			data.Height = static_cast<unsigned int>(height);

			WindowResizeEvent _event(width, height);
			data.EventCallback(_event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent _event;
			data.EventCallback(_event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
			{
				KeyPressedEvent _event(key, 0);
				data.EventCallback(_event);
			}
			else if (action == GLFW_RELEASE)
			{
				KeyReleasedEvent _event(key);
				data.EventCallback(_event);
			}
			else if (action == GLFW_REPEAT)
			{
				KeyPressedEvent _event(key, 1);
				data.EventCallback(_event);
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS)
			{
				MouseButtonPressedEvent _event(button);
				data.EventCallback(_event);
			}
			else if (action == GLFW_RELEASE)
			{
				MouseButtonReleasedEvent _event(button);
				data.EventCallback(_event);
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent _event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.EventCallback(_event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent _event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.EventCallback(_event);
		});
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.VSync;
	}

	double WindowsWindow::GetCurrentUpTime() const
	{
		return glfwGetTime();
	}
}