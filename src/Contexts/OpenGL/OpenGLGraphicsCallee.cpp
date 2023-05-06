#include "elysium_pch.h"
#include "OpenGLGraphicsCallee.h"

#include <gl/glew.h>

namespace Elysium
{
	void OpenGLGraphicsCallee::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		glDisable(GL_FRAMEBUFFER_SRGB); // Disable framebuffer gamma correction - handle manually
	}
	
	void OpenGLGraphicsCallee::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
	
	void OpenGLGraphicsCallee::SetColor(const Math::Vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLGraphicsCallee::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLGraphicsCallee::ClearColorBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLGraphicsCallee::ClearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLGraphicsCallee::ClearDepthAndStencilBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	
	void OpenGLGraphicsCallee::SetDepthTesting(bool state)
	{
		if (state)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
	
	void OpenGLGraphicsCallee::EnableFaceCulling(bool state)
	{
		if (state)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
	
	void OpenGLGraphicsCallee::SetFaceCulling(bool front)
	{
		if (front)
			glCullFace(GL_FRONT);
		else
			glCullFace(GL_BACK);
	}
	
	void OpenGLGraphicsCallee::SetMultisampling(bool enabled)
	{
		if (enabled)
			glEnable(GL_MULTISAMPLE);
		else
			glDisable(GL_MULTISAMPLE);
	}
	
	void OpenGLGraphicsCallee::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	bool OpenGLGraphicsCallee::IsShaderBinarySupported()
	{
		return false;

		int32_t nFormats = 0;
		glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &nFormats);
		return nFormats != 0;
	}

	void OpenGLGraphicsCallee::DrawTriangles(uint32_t size)
	{
		glDrawArrays(GL_TRIANGLES, 0, size);
	}

	void OpenGLGraphicsCallee::DrawLines(uint32_t size)
	{
		glDrawArrays(GL_LINES, 0, size);
	}

	void OpenGLGraphicsCallee::BindTexture(uint32_t id, uint32_t index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void OpenGLGraphicsCallee::DrawIndexed(const Shared<VertexArray>& vao, uint32_t index)
	{
		uint32_t count = index ? index : vao->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}