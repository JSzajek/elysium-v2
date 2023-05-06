#pragma once

#include "Elysium/Graphics/TransformFeedback.h"

namespace Elysium
{
	class OpenGLTransformFeedback : public TransformFeedback
	{
	public:
		OpenGLTransformFeedback();
		virtual ~OpenGLTransformFeedback() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t GetRenderID() const { return m_id; }

		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		inline virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffers() const override { return m_vertexBuffer; }

		virtual void Draw() override;
	private:
		uint32_t m_id;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
	};
}