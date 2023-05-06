#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLShaderAssembler.h"

#include "Elysium/Logging/Log.h"

#include "Elysium/Utils/FileUtils.h"
#include "Elysium/Utils/StringUtils.h"

#include "Elysium/Graphics/GraphicsCalls.h"

#include <shaderc/shaderc.hpp>

#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include <gl/glew.h>

namespace Elysium
{
	namespace Utils
	{
		static GLenum ShaderTypeFromString(const std::string& type)
		{
			switch (StringUtils::StrHash(type))
			{
			case "vertex"_:		return GL_VERTEX_SHADER;
			case "fragment"_:	return GL_FRAGMENT_SHADER;
			case "pixel"_:		return GL_FRAGMENT_SHADER;
			case "geometry"_:	return GL_GEOMETRY_SHADER;
			case "compute"_:	return GL_COMPUTE_SHADER;
			default:
			{
				ELYSIUM_CORE_ASSERT(false, "Unknown shader type!");
				return 0;
			}
			}
		}

		static ShaderType StageToShaderType(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:		return ShaderType::Vertex;
			case GL_FRAGMENT_SHADER:	return ShaderType::Fragment;
			case GL_GEOMETRY_SHADER:	return ShaderType::Geometry;
			case GL_COMPUTE_SHADER:		return ShaderType::Compute;
			}
			ELYSIUM_CORE_ASSERT(false);
			return ShaderType::None;
		}

		static GLenum ShaderTypeToStage(ShaderType type)
		{
			switch (type)
			{
			case ShaderType::Vertex:		return GL_VERTEX_SHADER;
			case ShaderType::Fragment:		return GL_FRAGMENT_SHADER;
			case ShaderType::Geometry:		return GL_GEOMETRY_SHADER;
			case ShaderType::Compute:		return GL_COMPUTE_SHADER;
			}
			return 0;
		}

		static ShaderType ExtensionToShaderType(const std::string& extension)
		{
			switch (StringUtils::StrHash(extension))
			{
			case ".vert"_: return ShaderType::Vertex;
			case ".frag"_: return ShaderType::Fragment;
			case ".geom"_: return ShaderType::Geometry;
			case ".comp"_: return ShaderType::Compute;
			default:
			{
				ELYSIUM_CORE_ASSERT(false, "Unknown shader type!");
				return ShaderType::None;
			}
			}
		}

		static GLenum ExtensionToType(const std::string& extension)
		{
			switch (StringUtils::StrHash(extension))
			{
			case ".vert"_: return GL_VERTEX_SHADER;
			case ".frag"_: return GL_FRAGMENT_SHADER;
			case ".geom"_: return GL_GEOMETRY_SHADER;
			case ".comp"_: return GL_COMPUTE_SHADER;
			default:
			{
				ELYSIUM_CORE_ASSERT(false, "Unknown shader type!");
				return 0;
			}
			}
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:		return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER:	return "GL_FRAGMENT_SHADER";
			case GL_GEOMETRY_SHADER:	return "GL_GEOMETRY_SHADER";
			case GL_COMPUTE_SHADER:		return "GL_COMPUTE_SHADER";
			}
			ELYSIUM_CORE_ASSERT(false);
			return nullptr;
		}

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:		return shaderc_glsl_vertex_shader;
			case GL_FRAGMENT_SHADER:	return shaderc_glsl_fragment_shader;
			case GL_GEOMETRY_SHADER:	return shaderc_glsl_geometry_shader;
			case GL_COMPUTE_SHADER:		return shaderc_glsl_compute_shader;
			}
			ELYSIUM_CORE_ASSERT(false, "Unknown shader stage!");
			return (shaderc_shader_kind)0;
		}

		static const char* GetCacheDirectory()
		{
			return "/cache";
		}

		static std::string TryCreateCacheDirectory(const std::string& currentDirectory)
		{
			std::string cacheDirectory = currentDirectory + GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directory(cacheDirectory);

			return cacheDirectory;
		}

		static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:		return ".cached_opengl.vert";
			case GL_FRAGMENT_SHADER:	return ".cached_opengl.frag";
			case GL_GEOMETRY_SHADER:	return ".cached_opengl.geom";
			case GL_COMPUTE_SHADER:		return ".cached_opengl.comp";
			}
			ELYSIUM_CORE_ASSERT(false, "Unknown shader stage!");
			return "";
		}
	}

	bool OpenGLShaderAssembler::Compile(uint32_t& id, const ShaderSource& source) const
	{
		if (GraphicsCalls::IsShaderBinarySupported()) // switch to pre-compiling
		{
			return false;
		}
		else
		{
			// On-demand compiling shader
			std::string errorString;
			if (!OnDemandCompile(id, source, errorString))
			{
				ELYSIUM_CORE_ERROR("Shader Compilation Failure:\n\t{0}", errorString);
				return false;
			}
		}
		return true;
	}

	bool OpenGLShaderAssembler::OnDemandCompile(uint32_t& id, const ShaderSource& shaderSources, std::string& errorString) const
	{
		GLuint program = glCreateProgram();

		if (shaderSources.size() > MAX_SHADERS_CATEGORIES)
		{
			errorString = "Found Too Many Shaders In Source.";
			return false;
		}

		for (const auto& [type, source] : shaderSources)
		{
			GLuint shader = glCreateShader(Utils::ShaderTypeToStage(type));
			const char* c_source = source.c_str();
			glShaderSource(shader, 1, &c_source, 0);

			glCompileShader(shader);

			auto isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				auto maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				errorString = std::move("type: " + std::to_string((uint8_t)type) + "\n" + std::string(infoLog.data(), infoLog.size()));

				glDeleteShader(shader);

				return false;
			}
			glAttachShader(program, shader);
			glDeleteShader(shader);
		}

		glLinkProgram(program);

		auto isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			auto maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			errorString = std::move(std::string(infoLog.data(), infoLog.size()));

			// We don't need the program anymore.
			glDeleteProgram(program);

			ELYSIUM_CORE_ASSERT(false, "Shader Link Failed.");
			return false;
		}

		id = program;
		return true;
	}

	bool OpenGLShaderAssembler::CompileOrGetBinaries(uint32_t& id, const ShaderSource& sources, const std::string& currentDir, std::unordered_map<unsigned int, std::vector<uint32_t>>& sprvMap) const
	{

		//ELYSIUM_CORE_ERROR("Shader linking failed ({0}):\n{1}", output->m_filepath, infoLog.data());
		return false;
	}

	bool OpenGLShaderAssembler::CreateFromBinaries(uint32_t& id, const std::unordered_map<unsigned int, std::vector<uint32_t>>& sprivMap, std::string& errorString) const
	{
		GLuint program = glCreateProgram();

		for (auto&& [stage, spirv] : sprivMap)
		{
			GLuint shaderID = glCreateShader(stage);
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), static_cast<uint32_t>(spirv.size() * sizeof(uint32_t)));
			glSpecializeShaderARB(shaderID, "main", 0, nullptr, nullptr); //TODO::swap between ARB extension and normal based on current opengl version?
			glAttachShader(program, shaderID);
			glDeleteShader(shaderID);
		}

		glLinkProgram(program);
		auto isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			auto maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			errorString = std::move(std::string(infoLog.data(), infoLog.size()));

			// We don't need the program anymore.
			glDeleteProgram(program);

			id = -1;
			return false;
		}
		id = program;
		return true;
	}
}