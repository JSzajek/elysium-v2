#include "elysium_pch.h"

#include "iVec3.h"

namespace Elysium::Math
{
	const iVec3 iVec3::X_Axis	= iVec3(1, 0, 0);
	const iVec3 iVec3::Y_Axis	= iVec3(0, 1, 0);
	const iVec3 iVec3::Z_Axis	= iVec3(0, 0, 1);
	const iVec3 iVec3::Zero		= iVec3(0);
	const iVec3 iVec3::One		= iVec3(1);

	iVec3::iVec3()
		: x(0), y(0), z(0)
	{
	}

	iVec3::iVec3(int _x, int _y, int _z)
		: x(_x), y(_y), z(_z)
	{
	}

	iVec3::iVec3(int _value)
		: x(_value), y(_value), z(_value)
	{
	}

	iVec3::iVec3(const iVec3& other)
		: x(other.x), y(other.y), z(other.z)
	{
	}

	int& iVec3::operator[](int index)
	{
		return index == 0 ? x : index == 1 ? y : z;
	}

	const int iVec3::operator[](int index) const
	{
		return index == 0 ? x : index == 1 ? y : z;
	}
}