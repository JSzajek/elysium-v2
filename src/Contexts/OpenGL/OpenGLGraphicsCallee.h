#pragma once

#include "Elysium/Graphics/GraphicsCalls.h"

namespace Elysium
{
	class OpenGLGraphicsCallee : public GraphicsCallee
	{
	public:
		void Initialize() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	
		void SetColor(const Math::Vec4& color) override;

		void ClearBuffers() override;
		void ClearColorBuffer() override;
		void ClearDepthBuffer() override;
		void ClearDepthAndStencilBuffer() override;

		void SetDepthTesting(bool state) override;
		void EnableFaceCulling(bool state) override;
		void SetFaceCulling(bool front) override;
		void SetMultisampling(bool enabled) override;
		void SetLineWidth(float width) override;

		bool IsShaderBinarySupported() override;

		void DrawIndexed(const Shared<VertexArray>& vao, uint32_t index) override;
		void DrawTriangles(uint32_t size) override;
		void DrawLines(uint32_t size) override;

		void BindTexture(uint32_t id, uint32_t index) override;
	};
}
