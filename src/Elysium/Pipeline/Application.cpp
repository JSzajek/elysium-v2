#include "elysium_pch.h"

#include "Elysium/Pipeline/Application.h"
#include "Elysium/Pipeline/Input.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Logging/Instrumentor.h"

#include "Elysium/Graphics/GraphicsAPI.h"
#include "Elysium/Graphics/GraphicsCalls.h"
#include "Elysium/Graphics/RenderCommands.h"

#include "Elysium/Factories/ShaderFactory.h"

#include "Elysium/Renderer/RendererBase.h"

#include "Elysium/Scene/Time.h"
#include "Elysium/Scene/CoreUniformBuffers.h"

namespace Elysium
{
	Application* Application::s_instance = nullptr;

	Application::Application(const std::string& name)
	{
		Initialize(WindowProperties(name));
	}

	Application::Application(const std::string& name, const uint16_t width, const uint16_t height)
	{
		Initialize(WindowProperties(name, width, height));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Initialize(const WindowProperties& properties)
	{
		ELYSIUM_PROFILE_FUNCTION();

		ELYSIUM_CORE_ASSERT(!s_instance, "Application already exists.");

		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create(properties));
		m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		// TODO:: Make this configurable
		GraphicsAPI::SetAPI(API::OpenGL);
		GraphicsCalls::SetupCalle();

		ShaderFactory::Initialize();
		RenderCommands::InitializeDependencies();
		GlobalRendererBase::Initialize();

		CoreUniformBuffers::Initialize();

#ifdef ELYSIUM_DEBUG
		m_imGuiLayer = new ImGuiLayer();
		PushOverlay(m_imGuiLayer);
#endif
#ifdef ELYSIUM_RELEASE
		m_imGuiLayer = new ImGuiLayer();
		PushOverlay(m_imGuiLayer);
#endif
	}

	void Application::Run()
	{
		while (m_running)
		{
			//ELYSIUM_PROFILE_SCOPE("Run Loop");

			Time::UpdateTime(static_cast<float>(m_window->GetCurrentUpTime()));

			if (!m_minimized)
			{
				{
					//ELYSIUM_PROFILE_SCOPE("LayerStack - OnUpdate");

					for (Layer* layer : m_layerStack)
					{
						layer->OnUpdate();
					}
				}

				m_imGuiLayer->Begin();
				{
					//ELYSIUM_PROFILE_SCOPE("LayerStack - OnImGuiRender");
					for (Layer* layer : m_layerStack)
						layer->OnImGuiRender();
				}
				m_imGuiLayer->End();

			}
			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& _event)
	{
		//ELYSIUM_CORE_TRACE(_event.ToString());

		EventDispatcher dispatcher(_event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(_event);

			if (_event.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& _event)
	{
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& _event)
	{
		if (_event.GetWidth() == 0 || _event.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		m_minimized = false;
		//Renderer::OnWindowResize(_event.GetWidth(), _event.GetHeight());

		return false;
	}
}