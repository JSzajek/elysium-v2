#pragma once

#include "Elysium/Graphics/Buffer.h"

namespace Elysium
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		/// <summary>
		/// Constructor initializing a OpenGLVertexBuffer.
		/// </summary>
		/// <param name="size">The size of the vertex buffer</param>
		OpenGLVertexBuffer(size_t size);

		/// <summary>
		/// Constructor initializing a OpenGLVertexBuffer.
		/// </summary>
		/// <param name="vertices">The vertices data</param>
		/// <param name="size">The size of the vertex buffer</param>
		/// <param name="dynamic">Whether the vertex buffer is dynamic</param>
		OpenGLVertexBuffer(void* vertices, size_t size, bool dynamic);

		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~OpenGLVertexBuffer();

		/// <summary>
		/// Binds the buffer.
		/// </summary>
		virtual void Bind() const override;

		/// <summary>
		/// Unbinds the buffer.
		/// </summary>
		virtual void Unbind() const override;

		/// <summary>
		/// Gets the render id of the buffer.
		/// </summary>
		/// <returns>The render id</returns>
		inline virtual uint32_t GetRenderID() const override { return m_id; }
		
		/// <summary>
		/// Retrieves a reference to the render id.
		/// </summary>
		/// <returns>The reference to the render id</returns>
		virtual inline uint32_t& GetRenderIDRef() override { return m_id; };

		/// <summary>
		/// Sets the layout of the buffer.
		/// </summary>
		/// <param name="layout">The buffer layout</param>
		inline virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }

		/// <summary>
		/// Retrieves the layout of the buffer.
		/// </summary>
		/// <returns>The buffer layout</returns>
		inline virtual const BufferLayout& GetLayout() const override { return m_layout; }

		/// <summary>
		/// Sets the data in the index buffer.
		/// </summary>
		/// <param name="data">The data to set</param>
		/// <param name="size">The size of the data</param>
		virtual void SetData(const void* data, size_t size) override;
	private:
		uint32_t m_id;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		/// <summary>
		/// Constructor initializing a OpenGLIndexBuffer.
		/// </summary>
		/// <param name="count">The number of indices</param>
		OpenGLIndexBuffer(uint32_t count);

		/// <summary>
		/// Constructor initializing a OpenGLIndexBuffer.
		/// </summary>
		/// <param name="indices">The indices data</param>
		/// <param name="count">The number of indices</param>
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~OpenGLIndexBuffer();

		/// <summary>
		/// Binds the buffer.
		/// </summary>
		virtual void Bind() const override;

		/// <summary>
		/// Unbinds the buffer.
		/// </summary>
		virtual void Unbind() const override;

		/// <summary>
		/// Gets the render id of the buffer.
		/// </summary>
		/// <returns>The render id</returns>
		inline virtual uint32_t GetRenderID() const override { return m_id; }

		/// <summary>
		/// Retrieves a reference to the render id.
		/// </summary>
		/// <returns>The reference to the render id</returns>
		virtual uint32_t& GetRenderIDRef() override { return m_id; }

		/// <summary>
		/// Retrieves the number of indices in the index buffer.
		/// </summary>
		/// <returns>The number of indices</returns>
		inline virtual uint32_t GetCount() const override { return m_count; }

		/// <summary>
		/// Sets the data in the index buffer.
		/// </summary>
		/// <param name="data">The data to set</param>
		/// <param name="size">The size of the data</param>
		virtual void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t m_id;
		uint32_t m_count;
	};
}