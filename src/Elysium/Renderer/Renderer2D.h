#pragma once

#include "Elysium/Renderer/RendererBase.h"

namespace Elysium
{
	class Renderer2D : protected RendererBase
	{
	private:
		struct QuadVertex
		{
			Math::Vec3 Position;
			Math::Vec4 Color;
			Math::Vec2 TexCoord;
			int TexIndex = 0;
			int IsFont = 0;
			// MaskId

			// Editor Only
			int EntityId = -1;
		};

		Shared<VertexArray> m_QuadVAO;
		Shared<VertexBuffer> m_QuadVBO;

		uint32_t m_QuadIndexCount = 0;
		QuadVertex* m_QuadVertexBufferBase = NULL;
		QuadVertex* m_QuadVertexBufferPtr = NULL;
	public:
		Renderer2D();
	public:
		void Initialize();
		void ShutDown();

		void BeginScene();
		void EndScene();
	public:
		void DrawSprite(const struct RectTransformComponent& transform, const struct SpriteComponent& sprite);
		void DrawPanel();
		void DrawLabel();
	protected:
		void StartBatch() override;
		void NextBatch() override;
	private:
		void Flush();
	};
}

