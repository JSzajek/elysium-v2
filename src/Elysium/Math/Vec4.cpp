#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Vec4.h"

namespace Elysium::Math
{
	const Vec4 Vec4::X_Axis		= Vec4(1,  0,  0, 0);
	const Vec4 Vec4::Y_Axis		= Vec4(0,  1,  0, 0);
	const Vec4 Vec4::Z_Axis		= Vec4(0,  0,  1, 0);
	const Vec4 Vec4::W_Axis		= Vec4(0,  0,  0, 1);
	const Vec4 Vec4::Zero		= Vec4(0);
	const Vec4 Vec4::One		= Vec4(1);
	const Vec4 Vec4::Left		= Vec4(-1, 0,  0, 0); // (-1, 0,  0,  0)
	const Vec4 Vec4::Right		= Vec4(1,  0,  0, 0); // (1,  0,  0,  0)
	const Vec4 Vec4::Up			= Vec4(0,  1,  0, 0); // (0,  1,  0,  0)
	const Vec4 Vec4::Down		= Vec4(0, -1,  0, 0); // (0, -1,  0,  0)
	const Vec4 Vec4::Forward	= Vec4(0,  0, -1, 0); // (0,  0, -1,  0)
	const Vec4 Vec4::Back		= Vec4(0,  0,  1, 0); // (0,  0,  1,  0)

	Vec4::Vec4()
		: x(0), y(0), z(0), w(0)
	{
	}

	Vec4::Vec4(const float& _x, const float& _y, const float& _z, const float& _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	Vec4::Vec4(const float& _value)
		: x(_value), y(_value), z(_value), w(_value)
	{
	}

	Vec4::Vec4(const Vec3& other, float _w)
		: x(other.x), y(other.y), z(other.z), w(_w)
	{
	}

	Vec4::Vec4(float _x, const Vec3& other)
		: x(_x), y(other.x), z(other.y), w(other.z)
	{
	}

	Vec4::Vec4(const Vec2& first, const Vec2& second)
		: x(first.x), y(first.y), z(second.x), w(second.y)
	{
	}

	Vec4::Vec4(const Vec4& other)
		: x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	float& Vec4::operator[](int index)
	{
		ELYSIUM_ASSERT(index < 4, "Vec4: Out Of Index Axis Access.");
		return m_data[index];
	}

	const float Vec4::operator[](int index) const
	{
		ELYSIUM_ASSERT(index < 4, "Vec4: Out Of Index Axis Access.");
		return m_data[index];
	}

	Vec4 Vec4::operator+(const Vec4& r_val) const
	{
		return Vec4(x + r_val.x, y + r_val.y, z + r_val.z, w + r_val.w);
	}

	void Vec4::operator+=(const Vec4& r_val)
	{
		x += r_val.x;
		y += r_val.y;
		z += r_val.z;
		w += r_val.w;
	}

	Vec4 Vec4::operator-(const Vec4& r_val) const
	{
		return Vec4(x - r_val.x, y - r_val.y, z - r_val.z, w - r_val.w);
	}

	void Vec4::operator-=(const Vec4& r_val)
	{
		x -= r_val.x;
		y -= r_val.y;
		z -= r_val.z;
		w -= r_val.w;
	}

	Vec4 Vec4::operator*(const Vec4& r_val) const
	{
		return Vec4(x * r_val.x, y * r_val.y, z * r_val.z, w * r_val.w);
	}

	Vec4 Vec4::operator*(const float r_val) const
	{
		return Vec4(x * r_val, y * r_val, z * r_val, w * r_val);
	}

	Vec4 Vec4::operator*(const double r_val) const
	{
		return Vec4(static_cast<float>(x * r_val), static_cast<float>(y * r_val), static_cast<float>(z * r_val), static_cast<float>(w * r_val));
	}

	Vec4 Vec4::operator*(const int r_val) const
	{
		return Vec4(x * r_val, y * r_val, z * r_val, w * r_val);
	}

	void Vec4::operator*=(const Vec4& r_val)
	{
		x *= r_val.x;
		y *= r_val.y;
		z *= r_val.z;
		w *= r_val.w;
	}

	void Vec4::operator*=(const float r_val)
	{
		x *= r_val;
		y *= r_val;
		z *= r_val;
		w *= r_val;
	}

	void Vec4::operator*=(const double r_val)
	{
		x = static_cast<float>(x * r_val);
		y = static_cast<float>(y * r_val);
		z = static_cast<float>(z * r_val);
		w = static_cast<float>(w * r_val);
	}

	void Vec4::operator*=(const int r_val)
	{
		x *= r_val;
		y *= r_val;
		z *= r_val;
		w *= r_val;
	}

	Vec4 Vec4::operator/(const Vec4& r_val) const
	{
		return Vec4(x / r_val.x, y / r_val.y, z / r_val.z, w / r_val.w);
	}

	Vec4 Vec4::operator/(const float r_val) const
	{
		return Vec4(x / r_val, y / r_val, z / r_val, w / r_val);
	}

	void Vec4::operator/=(const Vec4& r_val)
	{
		x /= r_val.x;
		y /= r_val.y;
		z /= r_val.z;
		w /= r_val.w;
	}

	void Vec4::operator/=(const float r_val)
	{
		x /= r_val;
		y /= r_val;
		z /= r_val;
		w /= r_val;
	}

	Vec4 Vec4::operator-() const
	{
		return Vec4(-x, -y, -z, -w);
	}

	bool Vec4::operator==(const Vec4& r_val) const
	{
		return x == r_val.x && y == r_val.y && z == r_val.z && w == r_val.w;
	}

	bool Vec4::operator!=(const Vec4& r_val) const
	{
		return x != r_val.x || y != r_val.y || z != r_val.z || w != r_val.w;
	}

	bool Vec4::operator<(const Vec4& r_val) const
	{
		if (x == r_val.x)
		{
			if (y == r_val.y)
			{
				if (z == r_val.z)
				{
					return w < r_val.w;
				}
				return z < r_val.z;
			}
			return y < r_val.y;
		}
		return x < r_val.x;
	}

	bool Vec4::operator>(const Vec4& r_val) const
	{
		if (x == r_val.x)
		{
			if (y == r_val.y)
			{
				if (z == r_val.z)
				{
					return w > r_val.w;
				}
				return z > r_val.z;
			}
			return y > r_val.y;
		}
		return x > r_val.x;
	}

	bool Vec4::operator<=(const Vec4& r_val) const
	{
		if (x == r_val.x)
		{
			if (y == r_val.y) 
			{
				if (z == r_val.z)
				{
					return w <= r_val.w;
				}
				return z <= r_val.z;
			}
			return y < r_val.y;
		}
		return x < r_val.x;
	}

	bool Vec4::operator>=(const Vec4& r_val) const
	{
		if (x == r_val.x) 
		{
			if (y == r_val.y) 
			{
				if (z == r_val.z)
				{
					return w >= r_val.w;
				}
				return z >= r_val.z;
			}
			return y > r_val.y;
		}
		return x > r_val.x;
	}

	Vec4 Vec4::Sign() const
	{
		return Vec4(SGN(x), SGN(y), SGN(z), SGN(w));
	}

	Vec4 Vec4::Floor() const
	{
		return Vec4(std::floorf(x), std::floorf(y), std::floorf(z), std::floorf(w));
	}

	Vec4 Vec4::Ceil() const
	{
		return Vec4(std::ceilf(x), std::ceilf(y), std::ceilf(z), std::ceilf(w));
	}

	Vec4 Vec4::Round() const
	{
		return Vec4(std::roundf(x), std::roundf(y), std::roundf(z), std::roundf(w));
	}

	void Vec4::Snap(const Vec4& r_val)
	{
		x = Math::Snapped(x, r_val.x);
		y = Math::Snapped(y, r_val.y);
		z = Math::Snapped(z, r_val.z);
		w = Math::Snapped(z, r_val.z);
	}

	Vec4 Vec4::Snapped(const Vec4& r_val) const
	{
		return Vec4(Math::Snapped(x, r_val.x), Math::Snapped(y, r_val.y), Math::Snapped(z, r_val.z), Math::Snapped(w, r_val.w));
	}

	void Vec4::Normalize()
	{
		float len = x * x + y * y + z * z + w * w;
		if (len != 0)
		{
			len = std::sqrtf(len);
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}
	}

	Vec4 Vec4::Normalized() const
	{
		Vec4 result = *this;
		result.Normalize();
		return result;
	}

	bool Vec4::IsNormalized() const
	{
		return Math::IsEqualApprox(LengthSquared(), 1.0f, UNIT_EPSILON);
	}

	float Vec4::Length() const
	{
		return std::sqrtf((x * x) + (y * y) + (z * z) + (w * w));
	}

	float Vec4::LengthSquared() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	void Vec4::SetAxis(int axis, float val)
	{
		ELYSIUM_ASSERT(axis < 4, "Vec4: Out Of Index Axis Access.");
		m_data[axis] = val;
	}

	float Vec4::GetAxis(int axis) const
	{
		ELYSIUM_ASSERT(axis < 4, "Vec4: Out Of Index Axis Access.");
		return operator[](axis);
	}

	int Vec4::MinAxis() const
	{
		// TODO Implement
		//return x < y ? (x < z ? 0 : 2) : (y < z ? 1 : 2);
		return 0;
	}

	int Vec4::MaxAxis() const
	{
		// TODO Implement
		//return x < y ? (y < z ? 2 : 1) : (x < z ? 2 : 0);
		return 0;
	}

	Vec4 Vec4::Clamped(const float val) const
	{
		float len = Length();
		Vec4 temp = *this;
		if (len > 0 && val < len)
		{
			temp /= len;
			temp *= val;
		}
		return temp;
	}

	float Vec4::DistanceTo(const Vec4& r_val) const
	{
		return (r_val - *this).Length();
	}

	float Vec4::DistanceSquaredTo(const Vec4& r_val) const
	{
		return (r_val - *this).LengthSquared();
	}

	float Vec4::AngleTo(const Vec4& r_val) const
	{
		return std::atan2f(Cross(r_val).Length(), Dot(r_val));
	}

	Vec4 Vec4::DirectionTo(const Vec4& r_val) const
	{
		Vec4 result(r_val.x - x, r_val.y - y, r_val.z - z, r_val.w - w);
		result.Normalize();
		return result;
	}

	// Not correct?
	float Vec4::Dot(const Vec4& r_val) const
	{
		return x * r_val.x + y * r_val.y + z * r_val.z;
	}

	Vec4 Vec4::Cross(const Vec4& r_val) const
	{
		return Vec4((y * r_val.z) - (z * r_val.y),
					(z * r_val.x) - (x * r_val.z),
					(x * r_val.y) - (y * r_val.x), 1);
	}

	Vec4 Vec4::PosMod(const Vec4& r_val) const
	{
		return Vec4(PosModf(x, r_val.x), PosModf(y, r_val.y), PosModf(z, r_val.z), PosModf(w, r_val.w));
	}

	Vec4 Vec4::PosMod(const float r_val) const
	{
		return Vec4(PosModf(x, r_val), PosModf(y, r_val), PosModf(z, r_val), PosModf(w, r_val));
	}

	Vec4 Vec4::Project(const Vec4& r_val) const
	{
		return r_val * (Dot(r_val) / r_val.LengthSquared());
	}

	Vec4 Vec4::PlaneProject(const float val, const Vec4& r_val) const
	{
		return r_val - *this * (Dot(r_val) - val);
	}

	Vec4 Vec4::Lerp(const Vec4& r_val, const float weight) const
	{
		return Vec4(x + (weight * (r_val.x - x)),
					y + (weight * (r_val.y - y)),
					z + (weight * (r_val.z - z)),
					w + (weight * (r_val.w - w)));
	}

	bool Vec4::IsEqualApprox(const Vec4& val) const
	{
		return Math::IsEqualApprox(x, val.x) && Math::IsEqualApprox(y, val.y) && Math::IsEqualApprox(z, val.z) && Math::IsEqualApprox(w, val.w);
	}
}