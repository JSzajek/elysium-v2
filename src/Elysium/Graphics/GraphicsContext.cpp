#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Elysium/Graphics/GraphicsAPI.h"
#include "Elysium/Graphics/GraphicsContext.h"

#include "Contexts/OpenGL/OpenGLContext.h"

namespace Elysium
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		API temp = API::OpenGL;

		switch (temp)
		{
			case API::None:    ELYSIUM_CORE_ASSERT(false, "GraphicsAPI::None is currently not supported!"); return nullptr;
			case API::OpenGL:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		ELYSIUM_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}