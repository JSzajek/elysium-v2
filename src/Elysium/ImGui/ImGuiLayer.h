#pragma once

#include "Elysium/Pipeline/Layer.h"
#include "Elysium/ImGui/ImGuiBuild.cpp"

namespace Elysium
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& _event) override;

		void BlockEvents(bool block) { m_blockEvents = block; }

		void Begin();
		void End();
	private:
		struct ImGuiLayerFontData
		{
		public:
			std::array<unsigned short, 3> m_iconRanges_fa;
			std::array<unsigned short, 3> m_iconRanges_faBrands;
			std::array<unsigned short, 3> m_iconRanges_fontaudio;
			std::array<unsigned short, 3> m_iconRanges_kenny;
		};
	private:
		bool m_blockEvents;
		ImGuiLayerFontData m_fontData;
	};
}