#pragma once

#include <cstdint>
#include <memory>

namespace Elysium
{
	/// <summary>
	/// Class representing a uniform buffer graphics object.
	/// </summary>
	class UniformBuffer
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~UniformBuffer() = default;

		/// <summary>
		/// Sets the data of the uniform buffer object.
		/// </summary>
		/// <param name="data">The data to set</param>
		/// <param name="size">The byte size of the data</param>
		/// <param name="offset">The offset to insert the data</param>
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		/// <summary>
		/// Creates a uniform buffer.
		/// </summary>
		/// <param name="size">The size of the uniform buffer</param>
		/// <param name="binding">The binding point of the uniform buffer</param>
		/// <returns>The created uniform buffer</returns>
		static std::shared_ptr<UniformBuffer> Create(uint32_t size, uint16_t binding);
	};
}
