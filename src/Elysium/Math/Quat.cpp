#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Quat.h"
#include "Mat3.h"

namespace Elysium::Math
{
	Quat::Quat()
		: x(0), y(0), z(0), w(1)
	{
	}

	Quat::Quat(const Vec3& axis, float angle)
	{
		ELYSIUM_CORE_ASSERT(axis.IsNormalized(), "Quat: The Axis Vector is Not Normalized.");

		float dim = axis.Length();
		if (dim == 0)
		{
			x = y = z = w = 0;
		}
		else
		{
			float s = std::sinf(angle * 0.5f) / dim;
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
			w = std::cosf(angle * 0.5f);
		}
	}

	Quat::Quat(float xQuat, float yQuat, float zQuat, float wQuat)
		: x(xQuat), y(yQuat), z(zQuat), w(wQuat)
	{
	}
	
	Quat::Quat(float xRotation, float yRotation, float zRotation)
	{
		float half_a1 = yRotation * 0.5f;
		float half_a2 = xRotation * 0.5f;
		float half_a3 = zRotation * 0.5f;

		// R = Y(a1).X(a2).Z(a3) convention for Euler angles.
		// Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page A-6)
		// a3 is the angle of the first rotation, following the notation in this reference.

		float cos_a1 = std::cosf(half_a1);
		float sin_a1 = std::sinf(half_a1);
		float cos_a2 = std::cosf(half_a2);
		float sin_a2 = std::sinf(half_a2);
		float cos_a3 = std::cosf(half_a3);
		float sin_a3 = std::sinf(half_a3);

		x = sin_a1 * cos_a2 * sin_a3 + cos_a1 * sin_a2 * cos_a3;
		y = sin_a1 * cos_a2 * cos_a3 - cos_a1 * sin_a2 * sin_a3;
		z = -sin_a1 * sin_a2 * cos_a3 + cos_a1 * cos_a2 * sin_a3;
		w = sin_a1 * sin_a2 * sin_a3 + cos_a1 * cos_a2 * cos_a3;
	}

	Quat::Quat(const Vec3& euler)
		: Quat(euler.x, euler.y, euler.z)
	{
	}

	Quat::Quat(const Vec3& first, const Vec3& second)
	{
		auto cross = first.Cross(second);
		auto dot = first.Dot(second);
		if (dot < -1.0 + CMP_EPSILON)
		{
			x = z = w = 0;
			y = 1;
		}
		else
		{
			auto sqrt = std::sqrtf((1.0f + dot) * 2.0f);
			auto d_sqrt = 1.0f / sqrt;
			x = cross.x * d_sqrt;
			y = cross.y * d_sqrt;
			z = cross.z * d_sqrt;
			w = sqrt * 0.5f;
		}
	}

	Quat::Quat(const Quat& other)
		: x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	float& Quat::operator[](int index)
	{
		ELYSIUM_ASSERT(index < 4, "Quat: Out Of Index Axis Access.");
		return m_data[index];
	}

	const float Quat::operator[](int index) const
	{
		ELYSIUM_ASSERT(index < 4, "Quat: Out Of Index Axis Access.");
		return m_data[index];
	}

	Quat& Quat::operator=(const Quat& r_val)
	{
		x = r_val.x;
		y = r_val.y;
		z = r_val.z;
		w = r_val.w;
		return *this;
	}

	void Quat::operator+=(const Quat& r_val)
	{
		x += r_val.x;
		y += r_val.y;
		z += r_val.z;
		w += r_val.w;
	}

	Quat Quat::operator+(const Quat& r_val) const
	{
		return Quat(x + r_val.x, y + r_val.y, z + r_val.z, w + r_val.w);
	}

	void Quat::operator-=(const Quat& r_val)
	{
		x -= r_val.x;
		y -= r_val.y;
		z -= r_val.z;
		w -= r_val.w;
	}

	Quat Quat::operator-(const Quat& r_val) const
	{
		return Quat(x - r_val.x, y - r_val.y, z - r_val.z, w - r_val.w);
	}

	void Quat::operator*=(const Quat& r_val)
	{
		x *= r_val.x;
		y *= r_val.y;
		z *= r_val.z;
		w *= r_val.w;
	}

	Quat Quat::operator*(const Quat& r_val) const
	{
		return Quat(x * r_val.x, y * r_val.y, z * r_val.z, w * r_val.w);
	}

	Quat Quat::operator*(const Vec3& r_val) const
	{
		return Quat(x * r_val.x + y * r_val.z - z * r_val.y,
					w * r_val.y + z * r_val.x - x * r_val.z,
					w * r_val.z + x * r_val.y - y * r_val.x,
				   -x * r_val.x - y * r_val.y - z * r_val.z);
	}

	Quat Quat::operator*(float r_val) const
	{
		return Quat(x * r_val, y * r_val, z * r_val, w * r_val);
	}

	void Quat::operator/=(float r_val)
	{
		x /= r_val;
		y /= r_val;
		z /= r_val;
		w /= r_val;
	}

	Quat Quat::operator/(float r_val) const
	{
		return (*this) * (1.0f / r_val);
	}

	Quat Quat::operator-() const 
	{
		return Quat(-x, -y, -z, -w);
	}

	bool Quat::operator==(const Quat& r_val) const
	{
		return x == r_val.x && y == r_val.y && z == r_val.z && w == r_val.w;
	}

	bool Quat::operator!=(const Quat& r_val) const
	{
		return x != r_val.x || y != r_val.y || z != r_val.z || w != r_val.w;
	}

	float Quat::Dot(const Quat& r_val) const
	{
		return x * r_val.x + y * r_val.y + z * r_val.z + w * r_val.w;
	}

	void Quat::Normalize()
	{
		*this /= Length();
	}

	Quat Quat::Normalized() const
	{
		return *this / Length();
	}

	bool Quat::IsNormalized() const
	{
		return Math::IsEqualApprox(LengthSquared(), 1.0, UNIT_EPSILON);
	}

	float Quat::Length() const
	{
		return std::sqrtf(LengthSquared());
	}

	float Quat::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Quat Quat::Inverse() const
	{
		ELYSIUM_CORE_ASSERT(IsNormalized(), "Quat: Must Be Normalized");

		return Quat(-x, -y, -z, -w);
	}

	Quat Quat::Slerp(const Quat& r_val, const float weight) const
	{
		ELYSIUM_CORE_ASSERT(IsNormalized(), "Quat: The Beginning Quat Must Be Normalized");
		ELYSIUM_CORE_ASSERT(r_val.IsNormalized(), "Quat: The Ending Quat Must Be Normalized");
	
		Quat end;
		float omega, cosom, sinom, scale0, scale1;

		cosom = Dot(r_val);
		if (cosom < 0.0f)
		{
			cosom = -cosom;
			end.x = -r_val.x;
			end.y = -r_val.y;
			end.z = -r_val.z;
			end.w = -r_val.w;
		}
		else
		{
			end.x = r_val.x;
			end.y = r_val.y;
			end.z = r_val.z;
			end.w = r_val.w;
		}

		if ((1.0f - cosom) > CMP_EPSILON)
		{
			omega = std::acosf(cosom);
			sinom = std::sinf(omega);
			scale0 = std::sinf((1.0f - weight) * omega) / sinom;
			scale1 = std::sinf(weight * omega) / sinom;
		}
		else
		{
			scale0 = 1.0f - weight;
			scale1 = weight;
		}

		return Quat(scale0 * x + scale1 * end.x,
					scale0 * y + scale1 * end.y,
					scale0 * z + scale1 * end.z,
					scale0 * w + scale1 * end.w);
	}

	bool Quat::IsEqualApprox(const Quat& val) const
	{
		return Math::IsEqualApprox(x, val.x) && Math::IsEqualApprox(y, val.y) && Math::IsEqualApprox(z, val.z) && Math::IsEqualApprox(w, val.w);
	}

	Vec3 Quat::XForm(const Vec3& vec) const
	{
		ELYSIUM_CORE_ASSERT(IsNormalized(), "Quat: Must Be Normalized");

		Vec3 temp(x, y, z);
		Vec3 cross = temp.Cross(vec);
		return temp + ((cross * w) + temp.Cross(cross)) * 2.0f;
	}

	Vec3 Quat::XFormInverted(const Vec3& vec) const
	{
		return Inverse().XForm(vec);
	}

	Vec3 Quat::ToEuler() const
	{
		Mat3 rot(*this);
		return rot.GetRotationEuler();
	}

	Vec3 Quat::Rotate(const Quat& orientation, const Vec3& axis)
	{
		Vec3 uv;
		Vec3 uuv;
		Vec3 qvec(orientation.x, orientation.y, orientation.z);

		uv = qvec.Cross(axis);
		uuv = qvec.Cross(uv);
		uv *= (2.0f * orientation.w);
		uuv *= 2.0f;
		return axis + uv + uuv;
	}
}