#pragma once

#include "Elysium/Core/Asserts.h"
#include "Elysium/Graphics/RenderObject.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

namespace Elysium
{
	/// <summary>
	/// Enum representing data type for shaders.
	/// </summary>
	enum class ShaderDataType : unsigned char
	{
		None = 0, 
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	/// <summary>
	/// Retrieves the data size of the shader data type.
	/// </summary>
	/// <param name="type">The shader data type</param>
	/// <returns>Return the data size</returns>
	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;

			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;

			case ShaderDataType::Bool:		return 1;
		}

		ELYSIUM_ASSERT(false, "Unknown Shader Data Type");
		return 0;
	}

	/// <summary>
	/// Struct representing a buffer element.
	/// </summary>
	struct BufferElement
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		BufferElement() = default;

		/// <summary>
		/// Constructor initializing a BufferElement.
		/// </summary>
		/// <param name="type">The shader data type</param>
		/// <param name="name">The name of the buffer element</param>
		/// <param name="normalized">Whether the data type is normalized</param>
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		/// <summary>
		/// Constructor initializing a BufferElement.
		/// </summary>
		/// <param name="type"></param>
		/// <param name="offset"></param>
		/// <param name="name"></param>
		/// <param name="normalized"></param>
		BufferElement(ShaderDataType type, uint16_t offset, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(offset), Normalized(normalized)
		{
		}

		/// <summary>
		/// Retrieves the component count of the buffer element.
		/// </summary>
		/// <returns>The component count</returns>
		unsigned int GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;

				case ShaderDataType::Mat3:		return 3;
				case ShaderDataType::Mat4:		return 4;

				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;

				case ShaderDataType::Bool:		return 1;
			}

			ELYSIUM_ASSERT(false, "Unknown Shader Data Type");
			return 0;
		}
	public:
		std::string Name;
		ShaderDataType Type = ShaderDataType::None;
		uint16_t Size = 0;
		uint16_t Offset = 0;
		bool Normalized = false;
	};

	/// <summary>
	/// Class representing the layout of a buffer in terms of element types.
	/// </summary>
	class BufferLayout
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		BufferLayout() = default;

		/// <summary>
		/// Constructor initializing an BufferLayout.
		/// </summary>
		/// <param name="elements">The buffer layout elements</param>
		BufferLayout(const std::initializer_list<BufferElement>& elements) 
			: m_elements(elements), m_stride(0)
		{
			CalculateOffsetAndStride();
		}
		inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
		inline uint16_t GetStride() const { return m_stride; }
		inline uint16_t GetSize() const { return static_cast<uint16_t>(m_elements.size()); }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	private:
		/// <summary>
		/// Calculates the offset and stride of the buffer based on the elements.
		/// </summary>
		void CalculateOffsetAndStride()
		{
			uint16_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_elements;
		uint16_t m_stride;
	};

	/// <summary>
	/// Base render buffer abstract class.
	/// </summary>
	class RenderBuffer : public BindableRenderObject
	{
	};

	/// <summary>
	/// Abstract class representing a graphics vertex buffer.
	/// </summary>
	class VertexBuffer : public RenderBuffer
	{
	public:
		/// <summary>
		/// Sets the layout of the buffer.
		/// </summary>
		/// <param name="layout">The buffer layout</param>
		virtual void SetLayout(const BufferLayout& layout) = 0;

		/// <summary>
		/// Retrieves the layout of the buffer.
		/// </summary>
		/// <returns>The buffer layout</returns>
		virtual const BufferLayout& GetLayout() const = 0;
	
		/// <summary>
		/// Sets the data in the vertex buffer.
		/// </summary>
		/// <param name="data">The data to set</param>
		/// <param name="size">The size of the data</param>
		virtual void SetData(const void* data, size_t size) = 0;

		/// <summary>
		/// Create a vertex buffer.
		/// </summary>
		/// <param name="size">The size of the vertex buffer</param>
		/// <returns>The vertex buffer</returns>
		static std::shared_ptr<VertexBuffer> Create(size_t size);

		/// <summary>
		/// Create a vertex buffer.
		/// </summary>
		/// <param name="vertices">The vertices data</param>
		/// <param name="size">The size of the vertex buffer data</param>
		/// <param name="dynamic">True if the vertex buffer is dynamic</param>
		/// <returns>The vertex buffer</returns>
		static std::shared_ptr<VertexBuffer> Create(void* vertices, size_t size, bool dynamic = false);
	};

	/// <summary>
	/// Abstract class representing a graphics index buffer.
	/// 
	/// NOTE:: Currently only supports 32-bit indices
	/// </summary>
	class IndexBuffer : public RenderBuffer
	{
	public:
		/// <summary>
		/// Retrieves the number of indices in the index buffer.
		/// </summary>
		/// <returns>The number of indices</returns>
		virtual uint32_t GetCount() const = 0;

		/// <summary>
		/// Sets the data in the index buffer.
		/// </summary>
		/// <param name="data">The data to set</param>
		/// <param name="size">The size of the data</param>
		virtual void SetData(const void* data, uint32_t size) = 0;

		/// <summary>
		/// Create a index buffer.
		/// </summary>
		/// <param name="count">The number indices in the buffer</param>
		/// <returns>The index buffer</returns>
		static std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t count);

		/// <summary>
		/// Create a index buffer.
		/// </summary>
		/// <param name="indices">The indices data</param>
		/// <param name="count">The number of indices</param>
		/// <returns>The index buffer</returns>
		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}