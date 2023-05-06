#pragma once

#include "Elysium/Math/Maths.h"
#include "Elysium/Core/UUIDs.h"

#include "Elysium/Outlines/Templates.h"

#include <string>
#include <unordered_map>

namespace Elysium
{
	class Shader
	{
	private:
		friend class ShaderFactory;
	public:
		enum class Type : uint8_t
		{
			Vertex = 0, Geometry, Fragment
		};
	public:
		virtual ~Shader() = default;

		virtual bool IsCompiled() const = 0;
		virtual void SetIsCompiled(bool compiled) = 0;
		virtual UUID GetID() const = 0;
		virtual void SetID(const UUID& id) = 0;

		virtual uint32_t GetRenderID() const = 0;
		virtual uint32_t& GetRenderIDRef() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void FinalizeVarying(const char** varyings, uint8_t count, bool interleaved) = 0;

		virtual const std::string& GetName() const = 0;
	public:
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const Math::Vec2& vector) = 0;
		virtual void SetFloat3(const std::string& name, const Math::Vec3& vector) = 0;
		virtual void SetFloat4(const std::string& name, const Math::Vec4& vector) = 0;
		virtual void SetMat4(const std::string& name, const Math::Mat4& matrix) = 0;
	};
}