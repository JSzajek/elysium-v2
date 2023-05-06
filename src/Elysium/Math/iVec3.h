#pragma once

namespace Elysium::Math
{
	/// <summary>
	/// Struct representing a 3-dimensional integer vector.
	/// </summary>
	struct iVec3
	{
	public:
		static const iVec3 X_Axis;
		static const iVec3 Y_Axis;
		static const iVec3 Z_Axis;
		static const iVec3 Zero;
		static const iVec3 One;
	public:
		union
		{
			struct
			{
				int x, y, z;
			};
			int m_data[3];
		};
	public:
		iVec3();
		iVec3(int _x, int _y, int _z);
		iVec3(const int _value);
		iVec3(const iVec3& other);

		int& operator[](int index);
		const int operator[](int index) const;
	};
}