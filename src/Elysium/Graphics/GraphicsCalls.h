#pragma once

#include "Elysium/Core/Memory.h"
#include "Elysium/Math/Vec4.h"

#include "Elysium/Graphics/VertexArray.h"

#include <cstdint>

namespace Elysium
{
	class GraphicsCallee
	{
	public:
		virtual void Initialize() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetColor(const Math::Vec4& color) = 0;

		virtual void ClearBuffers() = 0;
		virtual void ClearColorBuffer() = 0;
		virtual void ClearDepthBuffer() = 0;
		virtual void ClearDepthAndStencilBuffer() = 0;

		virtual void SetDepthTesting(bool state) = 0;
		virtual void EnableFaceCulling(bool state) = 0;
		virtual void SetFaceCulling(bool front) = 0;
		virtual void SetMultisampling(bool enabled) = 0;
		virtual void SetLineWidth(float width) = 0;

		virtual bool IsShaderBinarySupported() = 0;

		virtual void DrawIndexed(const Shared<VertexArray>& vao, uint32_t index) = 0;
		virtual void DrawTriangles(uint32_t size) = 0;
		virtual void DrawLines(uint32_t size) = 0;

		virtual void BindTexture(uint32_t id, uint32_t index) = 0;
	};

	class GraphicsCalls
	{
		friend class Application;
	public:
		inline static void Initialize() { s_graphicsCalle->Initialize(); }
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_graphicsCalle->SetViewport(x, y, width, height); }

		inline static void SetColor(const Math::Vec4& color) { s_graphicsCalle->SetColor(color); }

		inline static void ClearBuffers() { s_graphicsCalle->ClearBuffers(); }
		inline static void ClearColorBuffer() { s_graphicsCalle->ClearColorBuffer(); }
		inline static void ClearDepthBuffer() { s_graphicsCalle->ClearDepthBuffer(); }
		inline static void ClearDepthAndStencilBuffer() { s_graphicsCalle->ClearDepthAndStencilBuffer(); }

		inline static void SetDepthTesting(bool state) { s_graphicsCalle->SetDepthTesting(state); }
		inline static void EnableFaceCulling(bool state) { s_graphicsCalle->EnableFaceCulling(state); }
		inline static void SetFaceCulling(bool front) { s_graphicsCalle->SetFaceCulling(front); }
		inline static void SetLineWidth(float width) { s_graphicsCalle->SetLineWidth(width); }
		inline static void SetMultisampling(bool enabled) { s_graphicsCalle->SetMultisampling(enabled); }

		inline static bool IsShaderBinarySupported() { return s_graphicsCalle->IsShaderBinarySupported(); }

		inline static void DrawIndexed(const Shared<VertexArray>& vao, uint32_t index = 0) { s_graphicsCalle->DrawIndexed(vao, index); }
		inline static void DrawTriangles(uint32_t size) { s_graphicsCalle->DrawTriangles(size); }
		inline static void DrawLines(uint32_t size) { s_graphicsCalle->DrawLines(size); }

		inline static void BindTexture(uint32_t id, uint32_t index) { s_graphicsCalle->BindTexture(id, index); }
	private:
		static void SetupCalle();
	private:
		static Unique<GraphicsCallee> s_graphicsCalle;
	};
}