#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Elysium/Graphics/TransformFeedback.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLTransformFeedback.h"

namespace Elysium
{
	std::shared_ptr<TransformFeedback> TransformFeedback::Create()
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return NULL;
		case API::OpenGL:
			return std::make_shared<OpenGLTransformFeedback>();
		}
		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return NULL;
	}
}