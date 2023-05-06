#pragma once

#include "Elysium/core/Base.h"

namespace Elysium
{
	class Query
	{
	public:
		virtual ~Query() { }

		virtual void Begin() const = 0;
		virtual void End() const = 0;

		virtual void Result(int32_t* base) = 0;
	public:
		static std::shared_ptr<Query> Create(uint32_t type);
	};
}