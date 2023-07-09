#pragma once

#include "Elysium/Core/Asserts.h"

namespace Elysium
{
	/// <summary>
	/// Enum representing the graphics api.
	/// </summary>
	enum class API
	{
		None = 0, OpenGL = 1
	};

	/// <summary>
	/// Class representing the graphics api.
	/// </summary>
	class GraphicsAPI
	{
	public:
		/// <summary>
		/// Set the graphics api.
		/// </summary>
		/// <param name="api">The api to set</param>
		static inline void SetAPI(API api)
		{
			ELYSIUM_CORE_ASSERT(s_api == API::None, "Changing the API After Context Creation is Undefined Behaviour.");
			s_api = api;
		}

		/// <summary>
		/// Retrieves the current graphics api.
		/// </summary>
		/// <returns>The current graphics api</returns>
		static inline API GetAPI() 
		{ 
			return s_api; 
		}
	private:
		inline static API s_api = API::None;
	};
}