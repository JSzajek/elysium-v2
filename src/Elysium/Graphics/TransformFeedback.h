#pragma once

#include "Elysium/Graphics/Buffer.h"

#include <memory>

namespace Elysium
{
	// Also known as StreamOutput in directX
	class TransformFeedback
	{
	public:
		virtual ~TransformFeedback() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetRenderID() const = 0;

		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffers() const = 0;

		virtual void Draw() = 0;
	public:
		static std::shared_ptr<TransformFeedback> Create();
	};
}