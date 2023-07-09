#pragma once

#include "Elysium/Core/Memory.h"

namespace Elysium
{
	/// <summary>
	/// Class representing graphics queries.
	/// </summary>
	class Query
	{
	public:
		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~Query() = default;

		/// <summary>
		/// Begins the query.
		/// </summary>
		virtual void Begin() const = 0;

		/// <summary>
		/// Ends the query.
		/// </summary>
		virtual void End() const = 0;

		/// <summary>
		/// Retrieves the result of the query.
		/// </summary>
		/// <param name="base">The pointer to insert the result into</param>
		virtual void Result(int32_t* base) = 0;
	public:
		/// <summary>
		/// Creates a graphics query.
		/// </summary>
		/// <param name="type">The type of query to create</param>
		/// <returns>The graphics query pointer</returns>
		static Shared<Query> Create(uint32_t type);
	};
}