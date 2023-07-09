#include "elysium_pch.h"

#include "Elysium/Graphics/GraphicsCalls.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLGraphicsCallee.h"

namespace Elysium
{
	Unique<GraphicsCallee> GraphicsCalls::s_graphicsCallee = nullptr;

	void GraphicsCalls::SetupCallee()
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return;
		case API::OpenGL:
			s_graphicsCallee = std::move(CreateUnique<OpenGLGraphicsCallee>());
			return;
		}
		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
	}
}