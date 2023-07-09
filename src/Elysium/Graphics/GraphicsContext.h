#pragma once

#include "Elysium/Core/Memory.h"

namespace Elysium
{
	/// <summary>
	/// Class representing a graphics context.
	/// </summary>
	class GraphicsContext
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~GraphicsContext() = default;

		/// <summary>
		/// Initializes the graphics context.
		/// </summary>
		virtual void Init() = 0;

		/// <summary>
		/// Swaps the graphics context buffer.
		/// </summary>
		virtual void SwapBuffers() = 0;

		/// <summary>
		/// Creates a graphics context from the passed window.
		/// </summary>
		/// <param name="window">The graphics context from the window</param>
		/// <returns>Pointer to the graphics context</returns>
		static Unique<GraphicsContext> Create(void* window);
	};
}