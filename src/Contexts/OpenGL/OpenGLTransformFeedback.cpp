#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLTransformFeedback.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Logging/Instrumentor.h"

#include <gl/glew.h>

namespace Elysium
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;

			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;

			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;

			case ShaderDataType::Bool:		return GL_BOOL;
		}

		ELYSIUM_ASSERT(false, "Unknown Shader Data Type");
		return 0;
	}

	OpenGLTransformFeedback::OpenGLTransformFeedback()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glGenTransformFeedbacks(1, &m_id);
	}

	OpenGLTransformFeedback::~OpenGLTransformFeedback()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteTransformFeedbacks(1, &m_id);
	}

	void OpenGLTransformFeedback::Bind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_id);
	}
	
	void OpenGLTransformFeedback::Unbind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}

	void OpenGLTransformFeedback::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_id);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffer->GetRenderID());
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}
	
	void OpenGLTransformFeedback::Draw()
	{
		glDrawTransformFeedback(GL_POINTS, m_id);
	}
}