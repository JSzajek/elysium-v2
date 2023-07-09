#pragma once

#include "Elysium/Core/Memory.h"
#include "Elysium/Math/Vec4.h"

#include "Elysium/Graphics/VertexArray.h"

#include <cstdint>

namespace Elysium
{
	/// <summary>
	/// Abstract class representing a receiver of
	/// graphics calls depending on its API implementation.
	/// </summary>
	class GraphicsCallee
	{
	public:
		/// <summary>
		/// Initializes the graphics callee.
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// Sets the graphics viewport.
		/// </summary>
		/// <param name="x">The x offset</param>
		/// <param name="y">The y offset</param>
		/// <param name="width">The width of the viewport</param>
		/// <param name="height">The height of the viewport</param>
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// Sets the clear color.
		/// </summary>
		/// <param name="color">The color to set</param>
		virtual void SetColor(const Math::Vec4& color) = 0;

		/// <summary>
		/// Clears all the buffer bits.
		/// </summary>
		virtual void ClearBuffers() = 0;

		/// <summary>
		/// Clears the color buffer bit.
		/// </summary>
		virtual void ClearColorBuffer() = 0;

		/// <summary>
		/// Clears the depth buffer bit.
		/// </summary>
		virtual void ClearDepthBuffer() = 0;

		/// <summary>
		/// Clears the depth and stencil buffer bit.
		/// </summary>
		virtual void ClearDepthAndStencilBuffer() = 0;

		/// <summary>
		/// Sets the depth testing state.
		/// </summary>
		/// <param name="state">True if depth testing is on</param>
		virtual void SetDepthTesting(bool state) = 0;

		/// <summary>
		/// Enables face culling.
		/// </summary>
		/// <param name="state">True if the face culling is enabled</param>
		virtual void EnableFaceCulling(bool state) = 0;

		/// <summary>
		/// Sets the state of the face culling.
		/// </summary>
		/// <param name="front">True if it is front face culling</param>
		virtual void SetFaceCulling(bool front) = 0;

		/// <summary>
		/// Sets the multi-sampling state.
		/// </summary>
		/// <param name="enabled">True if enabled</param>
		virtual void SetMultisampling(bool enabled) = 0;

		/// <summary>
		/// Sets the graphics line width.
		/// </summary>
		/// <param name="width">The width to set</param>
		virtual void SetLineWidth(float width) = 0;

		/// <summary>
		/// Retrieves whether shader binaries are supported.
		/// </summary>
		/// <returns>True if shader binaries are supported</returns>
		virtual bool IsShaderBinarySupported() = 0;

		/// <summary>
		/// Draw indexed.
		/// </summary>
		/// <param name="vao">The vao to draw from</param>
		/// <param name="count">The number of indexed elements to draw</param>
		virtual void DrawIndexed(const Shared<VertexArray>& vao, uint32_t count) = 0;

		/// <summary>
		/// Draw triangles.
		/// </summary>
		/// <param name="count">The number of triangles to draw</param>
		virtual void DrawTriangles(uint32_t count) = 0;

		/// <summary>
		/// Draw lines.
		/// </summary>
		/// <param name="count">The number of lines to draw</param>
		virtual void DrawLines(uint32_t count) = 0;

		/// <summary>
		/// Binds a texture.
		/// </summary>
		/// <param name="id">The texture id to bind</param>
		/// <param name="index">The index to bind to</param>
		virtual void BindTexture(uint32_t id, uint32_t index) = 0;
	};

	/// <summary>
	/// Class representing api-agnostic graphic calls.
	/// </summary>
	class GraphicsCalls
	{
		friend class Application;
	public:
		/// <summary>
		/// Initializes the graphics callee.
		/// </summary>
		inline static void Initialize() { s_graphicsCallee->Initialize(); }

		/// <summary>
		/// Sets the graphics viewport.
		/// </summary>
		/// <param name="x">The x offset</param>
		/// <param name="y">The y offset</param>
		/// <param name="width">The width of the viewport</param>
		/// <param name="height">The height of the viewport</param>
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_graphicsCallee->SetViewport(x, y, width, height); }

		/// <summary>
		/// Sets the clear color.
		/// </summary>
		/// <param name="color">The color to set</param>
		inline static void SetColor(const Math::Vec4& color) { s_graphicsCallee->SetColor(color); }

		/// <summary>
		/// Clears all the buffer bits.
		/// </summary>
		inline static void ClearBuffers() { s_graphicsCallee->ClearBuffers(); }

		/// <summary>
		/// Clears the color buffer bit.
		/// </summary>
		inline static void ClearColorBuffer() { s_graphicsCallee->ClearColorBuffer(); }

		/// <summary>
		/// Clears the depth buffer bit.
		/// </summary>
		inline static void ClearDepthBuffer() { s_graphicsCallee->ClearDepthBuffer(); }

		/// <summary>
		/// Clears the depth and stencil buffer bit.
		/// </summary>
		inline static void ClearDepthAndStencilBuffer() { s_graphicsCallee->ClearDepthAndStencilBuffer(); }

		/// <summary>
		/// Sets the depth testing state.
		/// </summary>
		/// <param name="state">True if depth testing is on</param>
		inline static void SetDepthTesting(bool state) { s_graphicsCallee->SetDepthTesting(state); }

		/// <summary>
		/// Enables face culling.
		/// </summary>
		/// <param name="state">True if the face culling is enabled</param>
		inline static void EnableFaceCulling(bool state) { s_graphicsCallee->SetFaceCulling(state); }

		/// <summary>
		/// Sets the state of the face culling.
		/// </summary>
		/// <param name="front">True if it is front face culling</param>
		inline static void SetFaceCulling(bool front) { s_graphicsCallee->SetFaceCulling(front); }

		/// <summary>
		/// Sets the multi-sampling state.
		/// </summary>
		/// <param name="enabled">True if enabled</param>
		inline static void SetMultisampling(bool enabled) { s_graphicsCallee->SetMultisampling(enabled); }

		/// <summary>
		/// Sets the graphics line width.
		/// </summary>
		/// <param name="width">The width to set</param>
		inline static void SetLineWidth(float width) { s_graphicsCallee->SetLineWidth(width); }

		/// <summary>
		/// Retrieves whether shader binaries are supported.
		/// </summary>
		/// <returns>True if shader binaries are supported</returns>
		inline static bool IsShaderBinarySupported() { return s_graphicsCallee->IsShaderBinarySupported(); }

		/// <summary>
		/// Draw indexed.
		/// </summary>
		/// <param name="vao">The vao to draw from</param>
		/// <param name="count">The number of indexed elements to draw</param>
		inline static void DrawIndexed(const Shared<VertexArray>& vao, uint32_t count = 0) { s_graphicsCallee->DrawIndexed(vao, count); }

		/// <summary>
		/// Draw lines.
		/// </summary>
		/// <param name="count">The number of lines to draw</param>
		inline static void DrawTriangles(uint32_t count) { s_graphicsCallee->DrawTriangles(count); }

		/// <summary>
		/// Binds a texture.
		/// </summary>
		/// <param name="id">The texture id to bind</param>
		/// <param name="index">The index to bind to</param>
		inline static void DrawLines(uint32_t count) { s_graphicsCallee->DrawLines(count); }

		/// <summary>
		/// Binds a texture.
		/// </summary>
		/// <param name="id">The texture id to bind</param>
		/// <param name="index">The index to bind to</param>
		inline static void BindTexture(uint32_t id, uint32_t index) { s_graphicsCallee->BindTexture(id, index); }
	private:
		/// <summary>
		/// Sets up the callee.
		/// </summary>
		static void SetupCallee();
	private:
		static Unique<GraphicsCallee> s_graphicsCallee;
	};
}