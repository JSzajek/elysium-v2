#pragma once

#include "Elysium/Graphics/GraphicsCalls.h"

namespace Elysium
{
	/// <summary>
	/// Graphics Callee implementation for a OpenGL graphics api.
	/// </summary>
	class OpenGLGraphicsCallee : public GraphicsCallee
	{
	public:
		/// <summary>
		/// Initializes the graphics callee.
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// Sets the graphics viewport.
		/// </summary>
		/// <param name="x">The x offset</param>
		/// <param name="y">The y offset</param>
		/// <param name="width">The width of the viewport</param>
		/// <param name="height">The height of the viewport</param>
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	
		/// <summary>
		/// Sets the clear color.
		/// </summary>
		/// <param name="color">The color to set</param>
		void SetColor(const Math::Vec4& color) override;

		/// <summary>
		/// Clears all the buffer bits.
		/// </summary>
		void ClearBuffers() override;

		/// <summary>
		/// Clears the color buffer bit.
		/// </summary>
		void ClearColorBuffer() override;

		/// <summary>
		/// Clears the depth buffer bit.
		/// </summary>
		void ClearDepthBuffer() override;

		/// <summary>
		/// Clears the depth and stencil buffer bit.
		/// </summary>
		void ClearDepthAndStencilBuffer() override;

		/// <summary>
		/// Sets the depth testing state.
		/// </summary>
		/// <param name="state">True if depth testing is on</param>
		void SetDepthTesting(bool state) override;

		/// <summary>
		/// Enables face culling.
		/// </summary>
		/// <param name="state">True if the face culling is enabled</param>
		void EnableFaceCulling(bool state) override;

		/// <summary>
		/// Sets the state of the face culling.
		/// </summary>
		/// <param name="front">True if it is front face culling</param>
		void SetFaceCulling(bool front) override;

		/// <summary>
		/// Sets the multi-sampling state.
		/// </summary>
		/// <param name="enabled">True if enabled</param>
		void SetMultisampling(bool enabled) override;

		/// <summary>
		/// Sets the graphics line width.
		/// </summary>
		/// <param name="width">The width to set</param>
		void SetLineWidth(float width) override;

		/// <summary>
		/// Retrieves whether shader binaries are supported.
		/// </summary>
		/// <returns>True if shader binaries are supported</returns>
		bool IsShaderBinarySupported() override;

		/// <summary>
		/// Draw indexed.
		/// </summary>
		/// <param name="vao">The vao to draw from</param>
		/// <param name="count">The number of indexed elements to draw</param>
		void DrawIndexed(const Shared<VertexArray>& vao, uint32_t count) override;

		/// <summary>
		/// Draw triangles.
		/// </summary>
		/// <param name="count">The number of triangles to draw</param>
		void DrawTriangles(uint32_t count) override;

		/// <summary>
		/// Draw lines.
		/// </summary>
		/// <param name="count">The number of lines to draw</param>
		void DrawLines(uint32_t count) override;

		/// <summary>
		/// Binds a texture.
		/// </summary>
		/// <param name="id">The texture id to bind</param>
		/// <param name="index">The index to bind to</param>
		void BindTexture(uint32_t id, uint32_t index) override;
	};
}
