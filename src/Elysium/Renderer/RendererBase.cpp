#include "elysium_pch.h"
#include "Elysium/Renderer/RendererBase.h"

namespace Elysium
{
	Unique<GlobalObjects> GlobalRendererBase::s_globals = CreateUnique<GlobalObjects>();

	void GlobalRendererBase::Initialize()
	{
		if (!s_globals->s_initialized)
		{
			s_globals->ScreenQuad = VertexArray::Create();
			float quadVertices[] =
			{
				// positions   // texture Coords
			   -1.0f,  1.0f,  0.0f, 1.0f,
			   -1.0f, -1.0f,  0.0f, 0.0f,
				1.0f, -1.0f,  1.0f, 0.0f,

			   -1.0f,  1.0f,  0.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
				1.0f,  1.0f,  1.0f, 1.0f
			};
			auto m_vbo = VertexBuffer::Create(quadVertices, 6 * 4 * sizeof(float));
			BufferLayout layout =
			{
				{ ShaderDataType::Float2,	"a_Position" },
				{ ShaderDataType::Float2,	"a_TextureCoords" },
			};
			m_vbo->SetLayout(layout);
			s_globals->ScreenQuad->AddVertexBuffer(m_vbo);

			s_globals->WhiteTexture = Texture2D::Create(1u, 1u);
			uint32_t whiteTextureData = 0xffffffff;
			s_globals->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

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

			s_globals->DefaultQuadIndices = IndexBuffer::Create(quadIndices, RendererCaps::MaxIndices);
			delete[] quadIndices;
		}
	}

	void RendererBase::ResetTextureSlot()
	{
		TextureSlotIndex = TEXTURE_SLOT_USER_POINT;
	}

	void RendererBase::BindTextures()
	{
		GlobalRendererBase::GetDefaultTexture()->Bind(TEXTURE_SLOT_DEFAULT);

		// Bind Textures
		for (unsigned int i = TEXTURE_SLOT_USER_POINT; i < TextureSlotIndex; ++i)
			TextureSlots[i]->Bind(i);
	}

	uint16_t RendererBase::FindTextureIndex(const Shared<Texture2D>& texture)
	{
		uint16_t textureIndex = 0;
		if (texture)
		{
			// Push back texture for binding
			for (uint16_t i = TEXTURE_SLOT_USER_POINT; i < TextureSlotIndex; ++i)
			{
				if (*TextureSlots[i] == *texture)
				{
					textureIndex = i;
					break;
				}
			}

			if (textureIndex == 0)
			{
				if (TextureSlotIndex + 1 > RendererCaps::MaxTextureSlots)
					return -1;

				textureIndex = TextureSlotIndex;
				TextureSlots[TextureSlotIndex++] = texture;
			}
		}
		return textureIndex;
	}

	RendererStatistics RendererBase::GetStatistics()
	{
		return Statistics;
	}

	void RendererBase::ResetStatistics()
	{
		memset(&Statistics, 0, sizeof(RendererStatistics));
	}
}