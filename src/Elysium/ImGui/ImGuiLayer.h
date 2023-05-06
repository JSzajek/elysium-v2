#pragma once

#include "Elysium/Pipeline/Layer.h"
#include "Elysium/ImGui/ImGuiBuild.cpp"

namespace Elysium
{
	class ImGuiLayer : public Layer
	{
	private:
		bool m_blockEvents;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& _event) override;

		void BlockEvents(bool block) { m_blockEvents = block; }

		void Begin();
		void End();
	};
}