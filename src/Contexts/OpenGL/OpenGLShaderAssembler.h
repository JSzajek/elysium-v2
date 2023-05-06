#pragma once

#include "Elysium/Factories/ShaderFactory.h"

namespace Elysium
{
	class OpenGLShaderAssembler : public ShaderAssembler
	{
	public:
		bool Compile(uint32_t& id, const ShaderSource& source) const override;
	private:
		bool OnDemandCompile(uint32_t& id, const ShaderSource& shaderSources, std::string& errorString) const;
		bool CompileOrGetBinaries(uint32_t& id, const ShaderSource& sources, const std::string& currentDir, std::unordered_map<unsigned int, std::vector<uint32_t>>& sprvMap) const;
		bool CreateFromBinaries(uint32_t& id, const std::unordered_map<unsigned int, std::vector<uint32_t>>& sprivMap, std::string& errorString) const;
	};
}