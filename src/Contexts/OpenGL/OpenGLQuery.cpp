#include "elysium_pch.h"

#include "Elysium/Logging/Instrumentor.h"

#include "Contexts/OpenGL/OpenGLQuery.h"

#include <gl/glew.h>

namespace Elysium
{
	OpenGLQuery::OpenGLQuery(uint32_t type)
		: m_type (type)
	{
		ELYSIUM_PROFILE_FUNCTION();

		glGenQueries(1, &m_id);
	}

	OpenGLQuery::~OpenGLQuery()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteQueries(1, &m_id);
	}

	void OpenGLQuery::Begin() const
	{
		glBeginQuery(static_cast<GLenum>(m_type), m_id);
	}

	void OpenGLQuery::End() const
	{
		glEndQuery(static_cast<GLenum>(m_type));
	}

	void OpenGLQuery::Result(int32_t* result)
	{
		glGetQueryObjectiv(m_id, GL_QUERY_RESULT, (GLint*)result);
	}
}