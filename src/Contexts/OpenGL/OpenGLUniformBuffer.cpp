#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLUniformBuffer.h"

#include <gl/glew.h>

namespace Elysium
{
	// NEVER USE 3-element type structures
	// https://stackoverflow.com/questions/38172696/should-i-ever-use-a-vec3-inside-of-a-uniform-buffer-or-shader-storage-buffer-o

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint16_t binding)
	{
		glCreateBuffers(1, &m_id);
		glNamedBufferData(m_id, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
	
		m_binding = binding;
	}
	
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		//glNamedBufferSubData(m_id, offset, size, data);
	}
}