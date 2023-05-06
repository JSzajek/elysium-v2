#pragma once

#include "Elysium/Graphics/Buffer.h"

namespace Elysium
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t size);
		OpenGLVertexBuffer(void* vertices, size_t size, bool dynamic);
		virtual ~OpenGLVertexBuffer();

		inline virtual uint32_t GetRenderID() const { return m_id; }

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void SetData(const void* data, size_t size) override;

		inline virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
		inline virtual const BufferLayout& GetLayout() const override { return m_layout; }
	private:
		uint32_t m_id;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t count);
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		inline virtual uint32_t GetCount() const override { return m_count; }
	private:
		uint32_t m_id;
		uint32_t m_count;
	};
}