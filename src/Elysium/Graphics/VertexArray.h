#pragma once

#include "Elysium/Core/Memory.h"

#include "Elysium/Graphics/Buffer.h"
#include "Elysium/Graphics/RenderObject.h"

#include <vector>

namespace Elysium
{
	/// <summary>
	/// Class representing a vertex array graphics object.
	/// </summary>
	class VertexArray : public IBindable
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~VertexArray() { }

		/// <summary>
		/// Adds a vertex buffer.
		/// </summary>
		/// <param name="buffer">The vertex buffer to add</param>
		virtual void AddVertexBuffer(const Shared<VertexBuffer>& buffer) = 0;

		/// <summary>
		/// Sets the index buffer.
		/// </summary>
		/// <param name="buffer">The index buffer to set</param>
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& buffer) = 0;

		/// <summary>
		/// Retrieves the attached vertex buffers.
		/// </summary>
		/// <returns>The vertex buffers</returns>
		virtual const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;

		/// <summary>
		/// Retrieves the attached index buffer.
		/// </summary>
		/// <returns>The index buffer</returns>
		virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;

	public:
		/// <summary>
		/// Sets the attribute layout.
		/// </summary>
		/// <param name="layout">The buffer layout to set</param>
		static void SetAttributeLayout(const BufferLayout& layout);

		/// <summary>
		/// Clear the attribute layout.
		/// </summary>
		/// <param name="layout">The number of attribute layouts to clear</param>
		/// <param name="offset">The offset to start clearing from</param>
		static void ClearAttributeLayout(uint8_t count, uint8_t offset = 0);

		/// <summary>
		/// Creates a vertex array.
		/// </summary>
		/// <returns>The created vertex array</returns>
		static Shared<VertexArray> Create();
	};
}