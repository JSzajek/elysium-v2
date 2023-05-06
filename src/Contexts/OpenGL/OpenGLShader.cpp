#include "elysium_pch.h"
#include "Contexts/OpenGL/OpenGLShader.h"

#include "Elysium/Logging/Instrumentor.h"

#include "Elysium/Graphics/GraphicsAPI.h"

#include <chrono>
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include <gl/glew.h>

namespace Elysium
{
	OpenGLShader::OpenGLShader()
		: m_id(0), m_compiled(false)
	{
	}

	OpenGLShader::OpenGLShader(uint32_t id)
		: m_id(id), m_compiled(false)
	{
	}

#if 0
	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_filepath(filepath)
	{
		ELYSIUM_PROFILE_FUNCTION();
	
		//TODO:: Missing File Exception and abort
		ELYSIUM_CORE_ASSERT(FileUtils::FileExists(filepath), "Shader File Doesn't Exist");
	
		auto cacheDir = Utils::TryCreateCacheDirectory(std::filesystem::path(filepath).parent_path().string());
	
		auto source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		
		if (Renderer::GetRenderSettings().ShaderBinariesCompliant && Renderer::GetRenderSettings().PrecompileShaders)
		{
			std::unordered_map<unsigned int, std::vector<uint32_t>> m_openglSPIRV;
			if (CompileOrGetBinaries(shaderSources, cacheDir, m_openglSPIRV))
				CreateProgram(m_openglSPIRV);
		}
		else
		{
			Compile(shaderSources);
		}
	
		// Get Name from Filepath
		std::filesystem::path path = filepath;
		m_name = path.stem().string();
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_filepath(), m_name(name)
	{
		ELYSIUM_PROFILE_FUNCTION();
	
		auto vertex = vertexSrc;
		auto frag = fragmentSrc;
	
		ShaderSource shaderSources =
		{
			{ GL_VERTEX_SHADER, vertex },
			{ GL_FRAGMENT_SHADER, frag }
		};
	
		Compile(shaderSources);
	}
#endif

	OpenGLShader::~OpenGLShader()
	{
		ELYSIUM_PROFILE_FUNCTION();

		glDeleteProgram(m_id);
	}

	void OpenGLShader::Bind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glUseProgram(m_id);
	}

	void OpenGLShader::Unbind() const
	{
		ELYSIUM_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::FinalizeVarying(const char** varyings, uint8_t count, bool interleaved)
	{
		ELYSIUM_PROFILE_FUNCTION();

		if (!m_compiled)
		{
			ELYSIUM_CORE_WARN("Attempting to Finalize an Uncompiled Shader.");
			return;
		}

		glTransformFeedbackVaryings(m_id, count, varyings, interleaved ? GL_INTERLEAVED_ATTRIBS : GL_SEPARATE_ATTRIBS);
	
		glLinkProgram(m_id);

		GLint status;
		glGetProgramiv(m_id, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) 
		{
			GLint infoLen = 0;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				if (char* buf = new char[infoLen];  buf)
				{
					glGetShaderInfoLog(m_id, infoLen, NULL, buf);
					ELYSIUM_CORE_WARN("Unsuccessful linking: {0}", std::string(buf));
					delete[] buf;
				}
			}
			m_compiled = false;
		}
	}

#if 0
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		ELYSIUM_PROFILE_FUNCTION();

		std::string result;
		std::ifstream stream(filepath, std::ios::in | std::ios::binary);

		if (stream)
		{
			stream.seekg(0, std::ios::end);
			size_t size = static_cast<size_t>(stream.tellg());
			if (size != -1)
			{
				result.resize(size);
				stream.seekg(0, std::ios::beg);
				stream.read(&result[0], size);
			}
			else
			{
				ELYSIUM_CORE_ERROR("Could Not Read From File '{0}'", filepath);
			}
		}
		else
		{
			ELYSIUM_CORE_ERROR("Shader: Couldn't Open Shader File {0}", filepath);
		}
		return result;
	}

	ShaderSource OpenGLShader::PreProcess(const std::string& _source)
	{
		ELYSIUM_PROFILE_FUNCTION();

		auto source = _source;

		ShaderSource sources;

		const char* typeToken = "#shader";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			ELYSIUM_CORE_ASSERT(eol != std::string::npos, "Syntax Error in Shader Source.");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			ELYSIUM_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid Shader Type Specified.");
			
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			sources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}
		return sources;
	}

	void OpenGLShader::Compile(const ShaderSource& shaderSources)
	{
		ELYSIUM_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();

		ELYSIUM_CORE_ASSERT(shaderSources.size() <= MAX_SHADERS_CATEGORIES, "Found Too Many Shaders In Source.");
		m_glShaderIds.reserve(MAX_SHADERS_CATEGORIES);

		for (auto& kv : shaderSources)
		{
			auto type = kv.first;
			const auto& source = kv.second;

			GLuint shader = glCreateShader(type);
			const char* c_source = source.c_str();
			glShaderSource(shader, 1, &c_source, 0);

			glCompileShader(shader);

			auto isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				auto maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				ELYSIUM_CORE_ERROR("type: {0}\r\n{1}", type, infoLog.data());
				ELYSIUM_CORE_ASSERT(false, " Shader Compilation Failure.");
				break;
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
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Don't leak shaders either.
			for (auto id : m_glShaderIds)
				glDeleteShader(id);

			ELYSIUM_CORE_ERROR("{0}", infoLog.data());
			ELYSIUM_CORE_ASSERT(false, "Shader Link Failed.");
			return;
		}

		m_id = program;
	}

	bool OpenGLShader::CompileOrGetBinaries(const ShaderSource& shaderSources, const std::string& currentDir, std::unordered_map<unsigned int, std::vector<uint32_t>>& sprivMap)
	{
		ELYSIUM_PROFILE_FUNCTION();

		ELYSIUM_CORE_ASSERT(shaderSources.size() <= MAX_SHADERS_CATEGORIES, "Found Too Many Shaders In Source.");

		GLuint program = glCreateProgram();
		
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, 420);
		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);
		
		const auto pathBase = currentDir + "/" + std::filesystem::path(m_filepath).filename().string();

		for (auto&& [stage, source] : shaderSources)
		{
			std::filesystem::path cachePath = pathBase + Utils::GLShaderStageCachedOpenGLFileExtension(stage);

			std::ifstream in(cachePath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = sprivMap[stage];
				data.resize(static_cast<uint32_t>(size) / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source.c_str(), source.size(), Utils::GLShaderStageToShaderC(stage), m_filepath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					m_compiled = false;
					ELYSIUM_CORE_ERROR("Shader {0} Couldn't Compile: {1}", m_filepath, module.GetErrorMessage()); //TODO:: Safely exit and mark as incomplete instead
					return false;
				}

				sprivMap[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());
				
				std::ofstream out(cachePath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = sprivMap[stage];
					out.write((char*)data.data(), static_cast<std::streamsize>(data.size()) * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
		return true;
	}

	void OpenGLShader::CreateProgram(const std::unordered_map<unsigned int, std::vector<uint32_t>>& sprivMap)
	{
		GLuint program = glCreateProgram();

		m_glShaderIds.reserve(MAX_SHADERS_CATEGORIES);
		for (auto&& [stage, spirv] : sprivMap)
		{
			GLuint shaderID = m_glShaderIds.emplace_back(glCreateShader(stage));
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
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			ELYSIUM_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_filepath, infoLog.data());

			// We don't need the program anymore.
			glDeleteProgram(program);
		}

		m_id = program;
		m_compiled = true;
	}

	void OpenGLShader::Reflect(uint32_t stage, const std::vector<uint32_t>& shaderData)
	{
		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		ELYSIUM_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", Utils::GLShaderStageToString(stage), m_filepath);
		ELYSIUM_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		ELYSIUM_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		ELYSIUM_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = static_cast<uint32_t>(compiler.get_declared_struct_size(bufferType));
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			uint16_t memberCount = static_cast<uint16_t>(bufferType.member_types.size());

			ELYSIUM_CORE_TRACE("  {0}", resource.name);
			ELYSIUM_CORE_TRACE("    Size = {0}", bufferSize);
			ELYSIUM_CORE_TRACE("    Binding = {0}", binding);
			ELYSIUM_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	void Shader::PreCompile(ShaderOutline& info, const std::string& filepath)
	{
		auto cacheDir = Utils::TryCreateCacheDirectory(std::filesystem::path(filepath).parent_path().string());
		const auto pathBase = cacheDir + "/" + std::filesystem::path(filepath).filename().string();
		
		auto shaderSources = OpenGLShader::PreProcess(OpenGLShader::ReadFile(filepath));

		// TODO:: Add functionality to bring in defines

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, 420);
#if ELYSIUM_DEBUG
		options.SetOptimizationLevel(shaderc_optimization_level_zero);
#elif ELYSIUM_RELEASE
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
#endif
		uint8_t shaderTypes = 0;
		std::list<std::filesystem::path>& filecache = info.CachePaths;
		auto compiled = true; // Assume compiling will be successful
		for (auto&& [stage, source] : shaderSources)
		{
			std::filesystem::path cachePath = pathBase + Utils::GLShaderStageCachedOpenGLFileExtension(stage);
			BIT_SET(shaderTypes, (int)Utils::StageToShaderType(stage));

			//std::ifstream in(cachePath, std::ios::in | std::ios::binary);
			if (FileUtils::FileExists(cachePath.generic_string()))
			{
				filecache.push_back(cachePath);
			}
			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source.c_str(), source.size(), Utils::GLShaderStageToShaderC(stage), filepath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					compiled = false;
					ELYSIUM_CORE_WARN("Shader {0} Couldn't Compile: {1}", filepath, module.GetErrorMessage()); //TODO:: Safely exit and mark as incomplete instead
					break;
				}

				auto data = std::vector<uint32_t>(module.cbegin(), module.cend());
				std::ofstream out(cachePath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					out.write((char*)data.data(), static_cast<std::streamsize>(data.size()) * sizeof(uint32_t));
					out.flush();
					out.close();
				}

				filecache.push_back(cachePath);
			}
		}

		if (compiled)
		{
			// Update the meta file with the shader types and compile last-modified time stamp
			info.Compiled = true;

			info.LastCompileDate = FileUtils::LastModifiedTime(filepath);
		}
		else
		{
			// Clean Up after partial failure
			for (const auto& file : filecache)
				std::filesystem::remove(file);

			filecache.clear();

			info.Compiled = false;
			info.LastCompileDate = -1;
		}
	}

	void Shader::GetCache(ShaderOutline& info)
	{
		if (!info.Compiled)
		{
			ELYSIUM_CORE_WARN("Missing cache files - aborting cache gathering.");
			return;
		}

		for (const auto& path : info.CachePaths)
		{
			if (FileUtils::FileExists(path.generic_string()))
			{
				auto stage = Utils::ExtensionToType(path.extension().generic_string());

				std::ifstream in(path, std::ios::in | std::ios::binary);
				if (in.is_open())
				{
					in.seekg(0, std::ios::end);
					auto size = in.tellg();
					in.seekg(0, std::ios::beg);

					auto& data = info.Cache[stage];
					data.resize(static_cast<uint32_t>(size) / sizeof(uint32_t));
					in.read((char*)data.data(), size);
				}
			}
			else
			{
				ELYSIUM_CORE_WARN("Missing cache files - aborting cache gathering.");
				info.Cache.clear();
				break;
			}
		}
	}
#endif

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		auto found = indexDirectory.find(name);
		if (found != indexDirectory.end())
		{
			return found->second;
		}
		else
		{
			if (failedDirectory.find(name) != failedDirectory.end())
				return -1;

			int index = glGetUniformLocation(m_id, name.c_str());
			if (index == -1)
			{
				ELYSIUM_CORE_WARN("Shader: Failed to Find Uniform {0}.", name);
				failedDirectory[name] = index;
			}
			else
			{
				indexDirectory[name] = index;
			}
			return index;
		}
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const Math::Vec2& vector)
	{
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const Math::Vec3& vector)
	{
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const Math::Vec4& vector)
	{
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}
	
	void OpenGLShader::UploadUniformMat4(const std::string& name, const Math::Mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.data);
	}
}