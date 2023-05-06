#include "elysium_pch.h"
#include "Renderer2D.h"

#include "Elysium/Scene/2DComponents.h"
#include "Elysium/Factories/ShaderFactory.h"
#include "Elysium/Graphics/GraphicsCalls.h"

namespace Elysium
{
	Renderer2D::Renderer2D()
		: RendererBase()
	{
	}

	void Renderer2D::Initialize()
	{
		m_QuadVAO = VertexArray::Create();
		m_QuadVBO = VertexBuffer::Create(RendererCaps::MaxVertices * sizeof(QuadVertex));
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TextureCoords" },
			{ ShaderDataType::Int, "a_TextureIndex" },
			{ ShaderDataType::Int, "a_IsFont" },
			{ ShaderDataType::Int, "a_EntityId" }
		};
		m_QuadVBO->SetLayout(layout);
		m_QuadVAO->AddVertexBuffer(m_QuadVBO);

		m_QuadVertexBufferBase = new QuadVertex[RendererCaps::MaxVertices];
		uint32_t* quadIndices = new uint32_t[RendererCaps::MaxIndices];

		// Generate Standard Indices
		uint32_t offset = 0;
		for (uint32_t i = 0; i < RendererCaps::MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}

		Shared<IndexBuffer> ibo = IndexBuffer::Create(quadIndices, RendererCaps::MaxIndices);
		m_QuadVAO->SetIndexBuffer(ibo);
		delete[] quadIndices;
	}

	void Renderer2D::ShutDown()
	{
		delete[] m_QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene()
	{
		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		Flush();

		ResetStatistics();
	}

	void Renderer2D::DrawSprite(const RectTransformComponent& rectTransform, const SpriteComponent& sprite)
	{
		if (m_QuadIndexCount >= RendererCaps::MaxIndices)
			NextBatch();

		const auto& transform = rectTransform.GetTransform();

		int textureIndex = FindTextureIndex(sprite.Texture);

		for (unsigned int i = 0; i < QUAD_VERTEX_COUNT; ++i)
		{
			m_QuadVertexBufferPtr->Position = transform * s_defaultQuadCoords[i];
			m_QuadVertexBufferPtr->Color = sprite.Color;
			m_QuadVertexBufferPtr->TexCoord = s_defaultTextureCoords[i];
			m_QuadVertexBufferPtr->TexIndex = textureIndex;
			m_QuadVertexBufferPtr->IsFont = false;
			m_QuadVertexBufferPtr->EntityId = 0;
			m_QuadVertexBufferPtr++;
		}

		m_QuadIndexCount += 6;

		Statistics.IndexCount += 6;
		Statistics.VertexCount += 4;
	}

	void Renderer2D::DrawPanel()
	{

	}

	void Renderer2D::DrawLabel()
	{

	}

	void Renderer2D::StartBatch()
	{
		m_QuadIndexCount = 0;
		m_QuadVertexBufferPtr = m_QuadVertexBufferBase;

		ResetTextureSlot();
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::Flush()
	{
		if (m_QuadIndexCount == 0)
			return;

		m_QuadVAO->Bind();

		const uint32_t dataSize = (uint32_t)((uint8_t*)m_QuadVertexBufferPtr - (uint8_t*)m_QuadVertexBufferBase);
		m_QuadVBO->SetData(m_QuadVertexBufferBase, dataSize);

		BindTextures();

		GraphicsCalls::DrawIndexed(m_QuadVAO, m_QuadIndexCount);

		m_QuadVAO->Unbind();

		++Statistics.DrawCalls;
	}
}