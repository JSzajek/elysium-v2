#pragma once

#include "Elysium/Events/Event.h"

#include <string>

namespace Elysium
{
	class Layer
	{
	protected:
		std::string m_debugName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnImGuiRender() { }
		virtual void OnEvent(Event& _event) { }

		inline const std::string& GetName() const { return m_debugName; }
	};
}