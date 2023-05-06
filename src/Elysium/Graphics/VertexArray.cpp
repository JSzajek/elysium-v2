#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Elysium/Graphics/VertexArray.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLVertexArray.h"

namespace Elysium
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}
}