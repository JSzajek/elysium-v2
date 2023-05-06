#pragma once

#include "Elysium/Core/Asserts.h"

namespace Elysium
{
	enum class API
	{
		None = 0, OpenGL = 1
	};

	class GraphicsAPI
	{
	public:
		static inline void SetAPI(API api)
		{
			ELYSIUM_CORE_ASSERT(s_api == API::None, "Changing the API After Context Creation is Undefined Behaviour.");
			s_api = api;
		}
		static inline API GetAPI() 
		{ 
			return s_api; 
		}
	private:
		inline static API s_api = API::None;
	};
}