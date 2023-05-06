#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Elysium/Graphics/Query.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLQuery.h"

namespace Elysium
{
	std::shared_ptr<Query> Query::Create(uint32_t type)
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return std::make_shared<OpenGLQuery>(type);
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}
}