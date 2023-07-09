#pragma once

#include "Elysium/Core/Base.h"
#include "Elysium/Core/Memory.h"
#include "Elysium/Outlines/Templates.h"
#include "Elysium/Graphics/GraphicsAPI.h"

#include <unordered_map>

namespace Elysium
{
	// Forward declaration
	class Shader;
	class ShaderAssembler;

	#define MAX_SHADERS_CATEGORIES		4  // Vertex, Fragment/Pixel, Geometry, Compute

	enum class ShaderType : uint8_t
	{
		None = 0, 
		Vertex, 
		Fragment, 
		Geometry, 
		Compute
	};

	typedef std::unordered_map<ShaderType, std::string> ShaderSource;

	class ShaderAssembler
	{
	public:
		virtual bool Compile(uint32_t& id, const ShaderSource& source) const = 0;
	};

	class ShaderFactory
	{
	public:
		struct ShaderProgramSource
		{
			std::string m_vertex;
			std::string m_fragment;
		};
	public:
		static void Initialize();

		static Shared<Shader> Create(const std::string& filepath);
		static Shared<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		static Shared<Shader> CreateShader();
		static std::string ReadFile(const std::string& filepath);
		static ShaderSource PreProcess(const std::string& source);
		static ShaderType ShaderTypeFromString(const std::string& type);
	private:
		static Unique<ShaderAssembler> s_assembler;
		static std::string s_coreUBODefines;
	};
}