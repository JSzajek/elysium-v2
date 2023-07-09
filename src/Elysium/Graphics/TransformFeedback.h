#pragma once

#include "Elysium/Core/Memory.h"
#include "Elysium/Graphics/Buffer.h"
#include "Elysium/Graphics/RenderObject.h"

namespace Elysium
{
	/// <summary>
	/// Class represents a transform feedback graphics object.
	/// 
	/// Note: Also known as StreamOutput in directX
	/// </summary>
	class TransformFeedback : BindableRenderObject
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~TransformFeedback() { }

		/// <summary>
		/// Sets the vertex buffer of the transform feedback.
		/// </summary>
		/// <param name="buffer">The buffer to set</param>
		virtual void SetVertexBuffer(const Shared<VertexBuffer>& buffer) = 0;

		/// <summary>
		/// Retrieves the attached vertex buffer.
		/// </summary>
		/// <returns>The vertex buffer</returns>
		virtual const Shared<VertexBuffer>& GetVertexBuffers() const = 0;

		/// <summary>
		/// Draws the transform feedback buffer.
		/// </summary>
		virtual void Draw() = 0;
	public:
		/// <summary>
		/// Creates a transform feedback.
		/// </summary>
		/// <returns>The created transform feedback</returns>
		static Shared<TransformFeedback> Create();
	};
}