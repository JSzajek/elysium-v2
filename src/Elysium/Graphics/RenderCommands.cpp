#include "elysium_pch.h"
#include "Elysium/Graphics/RenderCommands.h"

#include "Elysium/Factories/ShaderFactory.h"

#include "Elysium/Graphics/VertexArray.h"
#include "Elysium/Graphics/GraphicsCalls.h"

namespace Elysium
{
	struct RenderCommandsData
	{
		Shared<VertexArray> m_vao;
		Shared<Shader> m_screenShader;
	};
	static RenderCommandsData s_data;

	void RenderCommands::DrawTexture(const Shared<FrameBuffer>& output, TextureDrawType type, uint32_t textureId)
	{
		GraphicsCalls::SetDepthTesting(false);
		output->Bind();

		s_data.m_vao->Bind();
		s_data.m_screenShader->Bind();
		GraphicsCalls::BindTexture(textureId, 0);
		GraphicsCalls::DrawTriangles(6);

		output->Unbind();
		GraphicsCalls::SetDepthTesting(true);
	}

	void RenderCommands::DrawTexture(const Shared<FrameBuffer>& output, TextureDrawType type, 
									 const Shared<Texture2D>& texture, const Shared<Shader>& drawShader)
	{
		GraphicsCalls::SetDepthTesting(false);
		output->Bind();

		s_data.m_vao->Bind();

		if (drawShader.get() == nullptr)
			s_data.m_screenShader->Bind();
		else
			drawShader->Bind();

		texture->Bind();
		GraphicsCalls::DrawTriangles(6);

		output->Unbind();
		GraphicsCalls::SetDepthTesting(true);
	}

	void RenderCommands::DrawScreenShader(const Shared<FrameBuffer>& output, const Shared<Shader>& shader)
	{
		GraphicsCalls::SetDepthTesting(false);
		output->Bind();

		s_data.m_vao->Bind();
		shader->Bind();
		GraphicsCalls::DrawTriangles(6);

		output->Unbind();
		GraphicsCalls::SetDepthTesting(true);
	}

	void RenderCommands::InitializeDependencies()
	{
		s_data.m_screenShader = ShaderFactory::Create("Content/Engine/shaders/default_screen.shader");

		s_data.m_screenShader->Bind();
		s_data.m_screenShader->SetInt("samplingTexture", 0);
		s_data.m_screenShader->Unbind();

		s_data.m_vao = VertexArray::Create();
		float quadVertices[] =
		{
			// positions  // texture Coords
		   -1.0f,  1.0f,  0.0f, 1.0f,
		   -1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

		   -1.0f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
		};

		const Shared<VertexBuffer> m_vbo = VertexBuffer::Create(quadVertices, 6 * 4 * sizeof(float));
		BufferLayout layout =
		{
			{ ShaderDataType::Float2,	"a_Position" },
			{ ShaderDataType::Float2,	"a_TextureCoords" },
		};
		m_vbo->SetLayout(layout);
		s_data.m_vao->AddVertexBuffer(m_vbo);
	}
}
