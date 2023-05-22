#pragma once

#include "Elysium/Renderer/RendererBase.h"

namespace Elysium
{
	class RendererGizmo : protected RendererBase
	{
	private:
		struct GizmoVertex
		{
			Math::Vec2 Position;
			Math::Vec2 TexCoord;
			int TexIndex = 0;

			// Editor Only
			int EntityId = -1;
		};

		struct GizmoLineVertex
		{
			Math::Vec2 Point;
			Math::Vec4 Color;
			int Type = 0;

			int EntityId = -1;
		};

		Shared<VertexArray> m_LineVAO;
		Shared<VertexBuffer> m_LineVBO;

		GizmoLineVertex* m_LineVertexBufferBase = nullptr;
		GizmoLineVertex* m_LineVertexBufferPtr = nullptr;
		uint32_t m_LineVertexCount = 0;

		Shared<VertexArray> m_QuadVAO;
		Shared<VertexBuffer> m_QuadVBO;

		uint32_t m_QuadIndexCount = 0;
		GizmoVertex* m_QuadVertexBufferBase = nullptr;
		GizmoVertex* m_QuadVertexBufferPtr = nullptr;

		Math::Vec2 m_QuadVertexPositions[4];
	public:
		RendererGizmo();
	public:
		void Initialize();
		void ShutDown();

		void BeginScene();
		void EndScene();

		void SetLineWidth(float lineWidth);
	public:
		void Draw(const struct GizmoRectComponent& transform);
	private:
		void DrawLine(const Math::Vec2& start, const Math::Vec2& end,
					  const Math::Vec4& color = Math::Vec4::One, int type = 0, int entityId = -1);
	protected:
		void StartBatch() override;
		void NextBatch() override;
	private:
		void Flush();
	};
}