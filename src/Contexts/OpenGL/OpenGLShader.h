#pragma once

#include "Elysium/Graphics/Shader.h"
#include "Elysium/Factories/ShaderFactory.h"

#include "Elysium/Math/Mat4.h"

#include "Elysium/Core/UUIDs.h"

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <string>

namespace Elysium
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		OpenGLShader(uint32_t id);
		virtual ~OpenGLShader() override;

		inline virtual bool IsCompiled() const override { return m_compiled; }
		inline virtual void SetIsCompiled(bool compiled) override { m_compiled = compiled; }

		inline virtual UUID GetID() const override { return Id; }
		inline virtual void SetID(const UUID& id) override { Id = id; }

		inline virtual uint32_t GetRenderID() const { return m_id; }
		inline virtual uint32_t& GetRenderIDRef() { return m_id; }

		void Bind() const override;
		void Unbind() const override;
		
		void FinalizeVarying(const char** varyings, uint8_t count, bool interleaved) override;

		inline const std::string& GetName() const override { return m_name; }
	public:
		inline void SetInt(const std::string& name, int value) override { UploadUniformInt(name, value); }
		inline void SetIntArray(const std::string& name, int* values, uint32_t count) override { UploadUniformIntArray(name, values, count); }
		inline void SetFloat(const std::string& name, float value) override { UploadUniformFloat(name, value); }
		inline void SetFloat2(const std::string& name, const Math::Vec2& vector) override { UploadUniformFloat2(name, vector); }
		inline void SetFloat3(const std::string& name, const Math::Vec3& vector) override { UploadUniformFloat3(name, vector); }
		inline void SetFloat4(const std::string& name, const Math::Vec4& vector) override { UploadUniformFloat4(name, vector); }
		inline void SetMat4(const std::string& name, const Math::Mat4& matrix) override { UploadUniformMat4(name, matrix); }
	protected:
		int GetUniformLocation(const std::string& name);
	private:
		void Compile(const ShaderSource& shaderSources);

		bool CompileOrGetBinaries(const ShaderSource& sources, const std::string& currentDir, std::unordered_map<unsigned int, std::vector<uint32_t>>& sprvMap);
		void CreateProgram(const std::unordered_map<unsigned int, std::vector<uint32_t>>& sprvMap);
		void Reflect(uint32_t stage, const std::vector<uint32_t>& shaderData);
	private:
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const Math::Vec2& vector);
		void UploadUniformFloat3(const std::string& name, const Math::Vec3& vector);
		void UploadUniformFloat4(const std::string& name, const Math::Vec4& vector);
		void UploadUniformMat4(const std::string& name, const Math::Mat4& matrix);
	private:
		uint32_t m_id;
		bool m_compiled;
		std::string m_name;
		std::unordered_map<std::string, uint16_t> indexDirectory;
		std::unordered_map<std::string, uint16_t> failedDirectory;

		std::vector<uint32_t> m_glShaderIds;

		std::string m_filepath;
	public:
		UUID Id;
	};
}