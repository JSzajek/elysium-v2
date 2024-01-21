#include "elysium_pch.h"
#include "Elysium/Factories/ShaderFactory.h"
#include "Elysium/Graphics/Shader.h"

#include "Elysium/Core/Asserts.h"
#include "Elysium/Utils/StringUtils.h"
#include "Elysium/Utils/FileUtils.h"

#include "Elysium/Graphics/GraphicsAPI.h"

#include "Contexts/OpenGL/OpenGLShaderAssembler.h"
#include "Contexts/OpenGL/OpenGLShader.h"

#include <fstream>

namespace Elysium
{
	Unique<ShaderAssembler> ShaderFactory::s_assembler = nullptr;
	std::string ShaderFactory::s_coreUBODefines;

	void ShaderFactory::Initialize()
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			break;
		case API::OpenGL:
			s_assembler = std::move(CreateUnique<OpenGLShaderAssembler>());
			break;
		default:
			ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
			break;
		}

		// Initialize the global defines string now
		// TODO:: Move default location to configurable or more integrated spot
		const std::filesystem::path coreUniformsPath = FileUtils::GetAssetPath("Content/Engine/shaders/core_uniforms.shader");
		if (FileUtils::FileExists(coreUniformsPath))
			s_coreUBODefines = ReadFile(coreUniformsPath.generic_string()) + "\r\n";
		else
			ELYSIUM_CORE_ASSERT(false, "Core Uniform Buffer Definitions Not Found.");
	}

	std::shared_ptr<Shader> ShaderFactory::Create(const std::string& filepath, std::string* errorMsg)
	{
		const std::string solvedFilepath = FileUtils::GetAssetPath_Str(filepath);

		if (FileUtils::FileExists(solvedFilepath))
		{
			std::shared_ptr<Shader> result = CreateShader();

			const ShaderSource source = PreProcess(ReadFile(solvedFilepath));
			if (!s_assembler->Compile(result->GetRenderIDRef(), source, errorMsg))
			{
				result->SetIsCompiled(false);
				return nullptr;
			}
			result->SetIsCompiled(true);
			return result;
		}
		ELYSIUM_CORE_WARN("Shader [{0}] File Doesn't Exist", filepath);
		return nullptr;
	}

	std::shared_ptr<Shader> ShaderFactory::Create(const std::string& name, const std::string& vertexSrc, 
												  const std::string& fragmentSrc, std::string* errorMsg)
	{
		const ShaderSource source =
		{
			{ ShaderType::Vertex, vertexSrc },
			{ ShaderType::Fragment, fragmentSrc }
		};

		std::shared_ptr<Shader> result = CreateShader();

		uint32_t id = 0;
		if (!s_assembler->Compile(result->GetRenderIDRef(), source, errorMsg))
		{
			return nullptr;
		}
		return result;
	}

	Elysium::Shared<Elysium::Shader> ShaderFactory::CreateFromCode(const std::string& code, std::string* errorMsg)
	{
		std::shared_ptr<Shader> result = CreateShader();

		const ShaderSource source = PreProcess(code);
		if (!s_assembler->Compile(result->GetRenderIDRef(), source, errorMsg))
		{
			result->SetIsCompiled(false);
			return nullptr;
		}
		result->SetIsCompiled(true);
		return result;
	}

	std::shared_ptr<Elysium::Shader> ShaderFactory::CreateShader()
	{
		switch (GraphicsAPI::GetAPI())
		{
		case API::None:
		{
			ELYSIUM_CORE_ASSERT(false, "Renderer API currently not set.");
			return nullptr;
			break;
		}
		case API::OpenGL:
			return std::make_shared<OpenGLShader>();
			break;
		}
		ELYSIUM_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	std::string ShaderFactory::ReadFile(const std::string& filepath)
	{
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

	Elysium::ShaderSource ShaderFactory::PreProcess(const std::string& source)
	{
		ShaderSource sources;

		const char* versionToken = "#version";
		size_t versionTokenLength = strlen(versionToken);

		const char* typeToken = "#shader";
		size_t typeTokenLength = strlen(typeToken);

		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t version_begin = source.find(versionToken, pos);
			size_t version_eol = source.find_first_of("\r\n", version_begin);

			size_t eol = source.find_first_of("\r\n", pos);
			ELYSIUM_CORE_ASSERT(eol != std::string::npos, "Syntax Error in Shader Source.");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			const ShaderType shaderType = ShaderTypeFromString(type);

			size_t nextLinePos = source.find_first_not_of("\r\n", version_eol);
			pos = source.find(typeToken, nextLinePos);

			std::stringstream stream;
			stream << source.substr(version_begin, version_eol - version_begin) << "\r\n";
			stream << s_coreUBODefines;
			stream << ((pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos));

			auto string = stream.str();
			sources[shaderType] = string;
		}
		return sources;
	}

	ShaderType ShaderFactory::ShaderTypeFromString(const std::string& type)
	{
		switch (StringUtils::StrHash(type))
		{
			case "vertex"_:			return ShaderType::Vertex;
			case "fragment"_:		return ShaderType::Fragment;
			case "pixel"_:			return ShaderType::Fragment;
			case "geometry"_:		return ShaderType::Geometry;
			case "compute"_:		return ShaderType::Compute;
			default:
			{
				ELYSIUM_CORE_ASSERT(false, "Unknown shader type!");
				return ShaderType::None;
			}
		}
	}
}