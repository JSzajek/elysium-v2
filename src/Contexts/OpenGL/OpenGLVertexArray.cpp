#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLVertexArray.h"

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

	OpenGLVertexArray::OpenGLVertexArray()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glGenVertexArrays(1, &m_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_id);
	}

	void OpenGLVertexArray::Bind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindVertexArray(m_id);
	}

	void OpenGLVertexArray::Unbind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		ELYSIUM_PROFILE_FUNCTION();

		ELYSIUM_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout set.");
		
		glBindVertexArray(m_id);
		buffer->Bind();

		uint16_t index = 0;
		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);

			// For Integer integer types
			if (element.Type >= ShaderDataType::Int && element.Type <= ShaderDataType::Int4)
				glVertexAttribIPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), layout.GetStride(), (const void*)element.Offset);
			else
				glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			
			index++;
		}

		m_vertexBuffers.push_back(buffer);

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		ELYSIUM_PROFILE_FUNCTION();

		glBindVertexArray(m_id);

		buffer->Bind();
		m_indexBuffers = buffer;

		glBindVertexArray(0);
	}

	void VertexArray::SetAttribLayout(const BufferLayout& layout)
	{
		uint16_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);

			// For Integer integer types
			if (element.Type >= ShaderDataType::Int && element.Type <= ShaderDataType::Int4)
				glVertexAttribIPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), layout.GetStride(), (const void*)element.Offset);
			else
				glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);

			index++;
		}
	}

	void VertexArray::ClearAttribLayout(uint8_t count, uint8_t offset)
	{
		for (uint8_t i = offset; i < count; ++i)
			glDisableVertexAttribArray(i);
	}
}