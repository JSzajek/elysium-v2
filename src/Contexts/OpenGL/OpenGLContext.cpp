#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLContext.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Logging/Log.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Elysium
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		ELYSIUM_CORE_ASSERT(m_windowHandle, "Window Handle is NULL.");
	}

#ifdef ELYSIUM_DEBUG
	void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* param)
	{
		std::stringstream stream;
		stream << "0x" << std::hex << type;

		std::string type_hex(stream.str());

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			ELYSIUM_CORE_ERROR("GLError - High::\n\ttype: {0}\n\tmessage: {1}", type_hex, message);
			ELYSIUM_CORE_ASSERT(false);
			break;
#if 0
		case GL_DEBUG_SEVERITY_MEDIUM:
			ELYSIUM_CORE_WARN("GLError - Medium::\n\ttype: {0}\n\tmessage: {1}", type_hex, message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			ELYSIUM_CORE_WARN("GLError - Low::\n\ttype: {0}\n\tmessage: {1}", type_hex, message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			ELYSIUM_CORE_INFO("GLError - Info::\n\ttype: {0}\n\tmessage: {1}", type_hex, message);
			break;
#endif
			//TODO:: Medium warning of 2 vertex shaders recompiling once in first draw pass
			// potential fix: "figure out all combinations of shaders and states you need, and draw one triangle using every combination."
			// However, since it is only once at start it may not be an issue at all.
		}
	}
#endif

	void OpenGLContext::Init()
	{
		//ELYSIUM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_windowHandle);
		
		auto success = glewInit();
		ELYSIUM_CORE_ASSERT(success == GLEW_OK, "GLEW Failed to Initialize.");
		
		ELYSIUM_CORE_INFO("OpenGL {0}", std::string((const char*)glGetString(GL_VERSION)));
		ELYSIUM_CORE_INFO("  Vendor   {0}", std::string((const char*)glGetString(GL_VENDOR)));
		ELYSIUM_CORE_INFO("  Renderer {0}", std::string((const char*)glGetString(GL_RENDERER)));

		#ifdef ELYSIUM_ENABLE_ASSERTS
			int major, minor;
			glGetIntegerv(GL_MAJOR_VERSION, &major);
			glGetIntegerv(GL_MINOR_VERSION, &minor);

			ELYSIUM_CORE_ASSERT(major > 3 || (major == 3 && minor >= 3), "Elysium requires atleaset OpenGL version 330.");
		#endif

		#ifdef ELYSIUM_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(DebugMessageCallback, 0);
		#endif
	}
	
	void OpenGLContext::SwapBuffers()
	{
		//ELYSIUM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_windowHandle);
	}
}