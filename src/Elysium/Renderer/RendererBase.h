#pragma once

#include "Elysium/Core/Memory.h"

#include "Elysium/Graphics/Constants.h"

#include "Elysium/Graphics/Texture.h"
#include "Elysium/Graphics/VertexArray.h"

#include "Elysium/Renderer/RendererDefines.h"

namespace Elysium
{
	struct GlobalObjects
	{
	public:
		bool s_initialized = false;
		Shared<Texture2D> WhiteTexture = nullptr;
		Shared<VertexArray> ScreenQuad = nullptr;
	};

	struct RendererStatistics
	{
	public:
		uint32_t DrawCalls = 0;
		uint32_t VertexCount = 0;
		uint32_t IndexCount = 0;

		float ProcessTime = 0;
	public:
		inline uint32_t GetTotalVertexCount() const { return VertexCount; }
		inline uint32_t GetTotalIndexCount() const { return IndexCount; }
		inline float GetProcessTime() const { return ProcessTime; }
	};

	class GlobalRendererBase
	{
	protected:
		static Unique<GlobalObjects> s_globals;
	public:
		static void Initialize();
		static inline const Shared<Texture2D> GetDefaultTexture() { return s_globals->WhiteTexture; }
	};

	class RendererBase
	{
	protected:
		std::array<Shared<Texture>, RendererCaps::MaxTextureSlots> TextureSlots;
		uint16_t TextureSlotIndex = TEXTURE_SLOT_USER_POINT;
		RendererStatistics Statistics;
	public:
		RendererStatistics GetStatistics();
	protected:
		virtual void StartBatch() = 0;
		virtual void NextBatch() = 0;
	protected:
		void ResetTextureSlot();
		void BindTextures();
		uint16_t FindTextureIndex(const Shared<Texture2D>& texture);
	protected:
		inline uint16_t GetTextureIndex() { return TextureSlotIndex; }
	protected:
		void ResetStatistics();
	};
}
