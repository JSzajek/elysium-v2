#include "elysium_pch.h"

#include "Elysium/Logging/Instrumentor.h"

#include "Contexts/OpenGL/OpenGLBuffer.h"

#include <gl/glew.h>

namespace Elysium
{
	/////////////////////////////////////////////////////////////////////////////////
	/// Vertex Buffer ///////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
	{
		ELYSIUM_PROFILE_FUNCTION();
		
		// Generate Dynamic Vertex Buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	//OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, bool dynamic)
	//{
	//	ELYSIUM_PROFILE_FUNCTION();
	//
	//	// Generate Vertex Buffer
	//	glGenBuffers(1, &m_id);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	//
	//	// Buffer Vertex Data
	//	glBufferData(GL_ARRAY_BUFFER, size, nullptr, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	//}

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, size_t size, bool dynamic)
	{
		ELYSIUM_PROFILE_FUNCTION();

		// Generate Vertex Buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);

		// Buffer Vertex Data
		glBufferData(GL_ARRAY_BUFFER, size, vertices, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_id);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	
	void OpenGLVertexBuffer::Unbind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, size_t size)
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////////////////////////////////////////////////////////////////////
	/// Index Buffer ////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count)
	{
		ELYSIUM_PROFILE_FUNCTION();

		// Generate Dynamic Index Buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_count(count)
	{
		ELYSIUM_PROFILE_FUNCTION();

		// Generate Index Buffer
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

		// Buffer Index Data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_id);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const void* data, uint32_t size)
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}
}