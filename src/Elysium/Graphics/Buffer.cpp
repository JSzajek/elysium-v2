#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Core/Memory.h"

#include "Elysium/Graphics/Buffer.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLBuffer.h"

namespace Elysium
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(size_t size)
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return CreateShared<OpenGLVertexBuffer>(size);
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* vertices, size_t size, bool dynamic)
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return CreateShared<OpenGLVertexBuffer>(vertices, size, dynamic);
		}
		
		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t count)
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return CreateShared<OpenGLIndexBuffer>(count);
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return CreateShared<OpenGLIndexBuffer>(indices, count);
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}
}