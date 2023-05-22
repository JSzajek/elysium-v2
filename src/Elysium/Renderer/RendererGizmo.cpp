#include "elysium_pch.h"
#include "Elysium/Renderer/RendererGizmo.h"

#include "Elysium/Graphics/GraphicsCalls.h"

#include "Elysium/Scene/2DComponents.h"

namespace Elysium
{
	RendererGizmo::RendererGizmo()
	{
	}

	void RendererGizmo::Initialize()
	{
		m_LineVAO = VertexArray::Create();
		m_LineVBO = VertexBuffer::Create(RendererCaps::MaxLineVertices * sizeof(GizmoLineVertex));
		BufferLayout layout =
		{
			{ ShaderDataType::Float2,	"a_Position" },
			{ ShaderDataType::Float4,	"a_Color" },
			{ ShaderDataType::Int,		"a_Type" },
			{ ShaderDataType::Int,		"a_EntityId" },
		};
		m_LineVBO->SetLayout(layout);
		m_LineVAO->AddVertexBuffer(m_LineVBO);

		m_LineVertexBufferBase = new GizmoLineVertex[RendererCaps::MaxLineVertices];

		m_QuadVAO = VertexArray::Create();
		m_QuadVBO = VertexBuffer::Create(RendererCaps::MaxVertices * sizeof(GizmoVertex));
		layout =
		{
			{ ShaderDataType::Float2,	"a_Position" },
			{ ShaderDataType::Float2,	"a_TextureCoords" },
			{ ShaderDataType::Int,		"a_TextureIndex" },
			{ ShaderDataType::Int,		"a_EntityId" },
		};
		m_QuadVBO->SetLayout(layout);
		m_QuadVAO->AddVertexBuffer(m_QuadVBO);

		m_QuadVertexBufferBase = new GizmoVertex[RendererCaps::MaxVertices];
		m_QuadVAO->SetIndexBuffer(GlobalRendererBase::GetDefaultQuadIndices());

		m_QuadVertexPositions[0] = Math::Vec2( 0.5f,  0.5f);
		m_QuadVertexPositions[1] = Math::Vec2( 0.5f, -0.5f);
		m_QuadVertexPositions[2] = Math::Vec2(-0.5f, -0.5f);
		m_QuadVertexPositions[3] = Math::Vec2(-0.5f,  0.5f);

		m_QuadVAO->SetIndexBuffer(GlobalRendererBase::GetDefaultQuadIndices());
	}

	void RendererGizmo::ShutDown()
	{
		delete[] m_QuadVertexBufferBase;
		delete[] m_LineVertexBufferBase;
	}

	void RendererGizmo::BeginScene()
	{
		GraphicsCalls::SetDepthTesting(false);
		StartBatch();
	}

	void RendererGizmo::EndScene()
	{
		Flush();

		GraphicsCalls::SetDepthTesting(true);
	}

	void RendererGizmo::SetLineWidth(float lineWidth)
	{
		GraphicsCalls::SetLineWidth(lineWidth);
	}

	void RendererGizmo::Draw(const struct GizmoRectComponent& transform)
	{
		const Math::Vec2 translation = transform.GetTranslation();
		const Math::Vec2 dimensions = transform.GetDimensions();

		const Math::Vec2 topLeft		= translation + Math::Vec2(0, 0);
		const Math::Vec2 topRight		= translation + Math::Vec2(dimensions.width, 0);
		const Math::Vec2 bottomRight	= translation + Math::Vec2(dimensions.width, dimensions.height);
		const Math::Vec2 bottomLeft		= translation + Math::Vec2(0, dimensions.height);

		const Math::Vec4 color = transform.Color;

		DrawLine(topLeft, topRight, color, 1, -1);
		DrawLine(topRight, bottomRight, color, 1, -1);
		DrawLine(bottomRight, bottomLeft, color, 1, -1);
		DrawLine(bottomLeft, topLeft, color, 1, -1);
	}

	void RendererGizmo::DrawLine(const Math::Vec2& start, const Math::Vec2& end, 
								 const Math::Vec4& color, int type, int entityId)
	{
		if (m_LineVertexCount > RendererCaps::MaxLineVertices)
			NextBatch();

		m_LineVertexBufferPtr->Point = start;
		m_LineVertexBufferPtr->Color = color;
		m_LineVertexBufferPtr->Type = type;
		m_LineVertexBufferPtr->EntityId = entityId;
		m_LineVertexBufferPtr++;

		m_LineVertexBufferPtr->Point = end;
		m_LineVertexBufferPtr->Color = color;
		m_LineVertexBufferPtr->Type = type;
		m_LineVertexBufferPtr->EntityId = entityId;
		m_LineVertexBufferPtr++;

		m_LineVertexCount += 2;
	}

	void RendererGizmo::StartBatch()
	{
		m_QuadIndexCount = 0;
		m_QuadVertexBufferPtr = m_QuadVertexBufferBase;

		m_LineVertexCount = 0;
		m_LineVertexBufferPtr = m_LineVertexBufferBase;
	}

	void RendererGizmo::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void RendererGizmo::Flush()
	{
		// Draw Gizmos (sprites) ---------------------------------
		if (m_QuadIndexCount > 0)
		{
			m_QuadVAO->Bind();

			uint32_t dataSize = (uint32_t)((uint8_t*)m_QuadVertexBufferPtr - (uint8_t*)m_QuadVertexBufferBase);
			m_QuadVBO->SetData(m_QuadVertexBufferBase, dataSize);

			GraphicsCalls::DrawIndexed(m_QuadVAO, m_QuadIndexCount);
		}

		// Draw Gizmo Lines --------------------------------------
		if (m_LineVertexCount > 0)
		{
			m_LineVAO->Bind();

			uint32_t dataSize = (uint32_t)((uint8_t*)m_LineVertexBufferPtr - (uint8_t*)m_LineVertexBufferBase);
			m_LineVBO->SetData(m_LineVertexBufferBase, dataSize);

			GraphicsCalls::DrawLines(m_LineVertexCount);
		}
	}
}