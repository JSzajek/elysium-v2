#pragma once

#include "Elysium/Math/Maths.h"
#include "Elysium/Core/UUIDs.h"

#include "Elysium/Graphics/RenderObject.h"
#include "Elysium/Outlines/Templates.h"

#include <string>
#include <unordered_map>

namespace Elysium
{
	/// <summary>
	/// Class representing a graphics shader.
	/// </summary>
	class Shader : public BindableRenderObject
	{
	private:
		friend class ShaderFactory;
	public:
		/// <summary>
		/// Enum representing a shader type.
		/// </summary>
		enum class Type : uint8_t
		{
			Vertex = 0, Geometry, Fragment
		};
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~Shader() = default;

		/// <summary>
		/// Retrieves whether the shader is compiled.
		/// </summary>
		/// <returns>True if it is compiled</returns>
		virtual bool IsCompiled() const = 0;

		/// <summary>
		/// Sets override whether the shader is compiled.
		/// </summary>
		/// <param name="compiled">The compiled state to set</param>
		virtual void SetIsCompiled(bool compiled) = 0;

		/// <summary>
		/// Retrieves the unique id of the shader.
		/// </summary>
		/// <returns>The unique id</returns>
		virtual UUID GetID() const = 0;

		/// <summary>
		/// Sets the unique id of the shader.
		/// </summary>
		/// <param name="id">The unique id to set</param>
		virtual void SetID(const UUID& id) = 0;

		/// <summary>
		/// Finalizes the passed varying parameters of the shader.
		/// </summary>
		/// <param name="varyings">The varyings to finalize</param>
		/// <param name="count">The number of parameters</param>
		/// <param name="interleaved">True if the parameters are interleaved</param>
		virtual void FinalizeVarying(const char** varyings, uint8_t count, bool interleaved) = 0;

		/// <summary>
		/// Sets the name of the shader.
		/// </summary>
		/// <returns>The name of the shader</returns>
		virtual const std::string& GetName() const = 0;
	public:
		/// <summary>
		/// Sets a int uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="value">The value to set</param>
		virtual void SetInt(const std::string& name, int value) = 0;

		/// <summary>
		/// Sets a int array uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="values">The values to set</param>
		/// <param name="count">The number of values</param>
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

		/// <summary>
		/// Sets a float uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="value">The value to set</param>
		virtual void SetFloat(const std::string& name, float value) = 0;

		/// <summary>
		/// Sets a float2 uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="value">The value to set</param>
		virtual void SetFloat2(const std::string& name, const Math::Vec2& value) = 0;

		/// <summary>
		/// Sets a float3 uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="value">The value to set</param>
		virtual void SetFloat3(const std::string& name, const Math::Vec3& value) = 0;

		/// <summary>
		/// Sets a float4 uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="value">The value to set</param>
		virtual void SetFloat4(const std::string& name, const Math::Vec4& value) = 0;

		/// <summary>
		/// Sets a mat4 uniform with the passed name to the passed value.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="value">The value to set</param>
		virtual void SetMat4(const std::string& name, const Math::Mat4& value) = 0;
	};
}