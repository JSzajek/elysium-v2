#include "elysium_pch.h"
#include "MathsUtils.h"

#include "Elysium/core/Asserts.h"

namespace Elysium::Math
{
	template<class T>
	T Min(const T& lhs, const T& rhs)
	{
		ELYSIUM_CORE_ASSERT(false, "Undefined Behaviour - Attempting to take minimum from undefined type.");
		return lhs;
	}

	template<>
	Math::Vec4 Min<Math::Vec4>(const Math::Vec4& lhs, const Math::Vec4& rhs)
	{
		Math::Vec4 min;
		for (uint8_t i = 0; i < 4; ++i)
			min[i] = MIN(lhs[i], rhs[i]);
		return min;
	}

	template<class T>
	T Max(const T& lhs, const T& rhs)
	{
		ELYSIUM_CORE_ASSERT(false, "Undefined Behaviour - Attempting to take maximum from undefined type.");
		return lhs;
	}

	template<>
	Math::Vec4 Max<Math::Vec4>(const Math::Vec4& lhs, const Math::Vec4& rhs)
	{
		Math::Vec4 min;
		for (uint8_t i = 0; i < 4; ++i)
			min[i] = MAX(lhs[i], rhs[i]);
		return min;
	}
}