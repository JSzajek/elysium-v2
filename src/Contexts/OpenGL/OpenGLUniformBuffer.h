#pragma once

#include "Elysium/Graphics/UniformBuffer.h"

namespace Elysium
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t size, uint16_t binding);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;
	private:
		uint32_t m_id;
		size_t m_binding;
	};
}