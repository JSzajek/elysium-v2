#pragma once

#include "Elysium/Core/Asserts.h"

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

namespace Elysium
{
	enum class ShaderDataType : unsigned char
	{
		None = 0, 
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

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

	struct BufferElement
	{
	public:
		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		BufferElement(ShaderDataType type, uint16_t offset, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(offset), Normalized(normalized)
		{
		}

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

	class BufferLayout
	{
	public:
		BufferLayout() = default;

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

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetRenderID() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	
		virtual void SetData(const void* data, size_t size) = 0;

		static std::shared_ptr<VertexBuffer> Create(size_t size);
		static std::shared_ptr<VertexBuffer> Create(void* vertices, size_t size, bool dynamic = false);
	};

	// Only supports 32 bit index buffers
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t count);
		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}