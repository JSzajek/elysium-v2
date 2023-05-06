#pragma once

#include "Elysium/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Elysium
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}