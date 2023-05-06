#pragma once

#include "Elysium/Graphics/Buffer.h"

namespace Elysium
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static void SetAttribLayout(const BufferLayout& layout);
		static void ClearAttribLayout(uint8_t count, uint8_t offset = 0);

		static std::shared_ptr<VertexArray> Create();
	};
}