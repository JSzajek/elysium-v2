#include "elysium_pch.h"

#include "Elysium/Core/Asserts.h"

#include "Mat3.h"

namespace Elysium::Math
{
	Mat3::Mat3()
	{
		std::memset(data, 0, sizeof(data));
	}

	Mat3::Mat3(const Mat3& other) 
	{
		std::memcpy(data, other.data, sizeof(data));
	}

	Mat3::Mat3(const Quat& quat)
	{
		SetQuat(quat);
	}

	Mat3::Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2)
	{
		columns[0] = row0;
		columns[1] = row1;
		columns[2] = row2;
	}

	Mat3::Mat3(float v00, float v01, float v02,
			   float v10, float v11, float v12,
			   float v20, float v21, float v22)
	{
		columns[0][0] = v00;
		columns[0][1] = v01;
		columns[0][2] = v02;

		columns[1][0] = v10;
		columns[1][1] = v11;
		columns[1][2] = v12;

		columns[2][0] = v20;
		columns[2][1] = v21;
		columns[2][2] = v22;
	}

	void Mat3::operator=(const Mat3& other)
	{
		std::memcpy(data, other.data, sizeof(data));
	}

	inline Mat3 Mat3::operator*(const Mat3& matrix) const
	{
		return Mat3(matrix.tdotx(columns[0]), matrix.tdoty(columns[0]), matrix.tdotz(columns[0]),
					matrix.tdotx(columns[1]), matrix.tdoty(columns[1]), matrix.tdotz(columns[1]),
					matrix.tdotx(columns[2]), matrix.tdoty(columns[2]), matrix.tdotz(columns[2]));
	}

	void Mat3::Orthonormalize()
	{
		Vec3 x = GetAxis(0);
		Vec3 y = GetAxis(1);
		Vec3 z = GetAxis(2);

		x.Normalize();
		y = (y - x * (x.Dot(y)));
		y.Normalize();
		z = (z - x * (x.Dot(z)) - y * (y.Dot(z)));
		z.Normalize();

		SetAxis(0, x);
		SetAxis(1, y);
		SetAxis(2, z);
	}

	Mat3 Mat3::Orthonormalized() const
	{
		Mat3 result = *this;
		result.Orthonormalize();
		return result;
	}

	float Mat3::Determinant() const
	{
		return columns[0][0] * (columns[1][1] * columns[2][2] - columns[2][1] * columns[1][2]) -
			   columns[1][0] * (columns[0][1] * columns[2][2] - columns[2][1] * columns[0][2]) +
			   columns[2][0] * (columns[0][1] * columns[1][2] - columns[1][1] * columns[0][2]);
	}

	const Mat3 Mat3::Inverse(bool* success) const
	{
		ELYSIUM_CORE_ASSERT("Not Implemented!");
		return Mat3();
	}

	void Mat3::Transpose()
	{
		ELYSIUM_CORE_ASSERT("Not Implemented!");
	}

	void Mat3::Scale(const Vec3& scale)
	{
		columns[0][0] *= scale.x;
		columns[0][1] *= scale.x;
		columns[0][2] *= scale.x;
		columns[1][0] *= scale.y;
		columns[1][1] *= scale.y;
		columns[1][2] *= scale.y;
		columns[2][0] *= scale.z;
		columns[2][1] *= scale.z;
		columns[2][2] *= scale.z;
	}

	Vec3 Mat3::GetRotationEuler() const
	{
		Mat3 result = Orthonormalized();
		auto determinant = result.Determinant();
		if (determinant < 0.0f)
			result.Scale(Vec3(-1));
		
		return result.GetEuler();
	}

	Vec3 Mat3::GetEulerXYZ() const
	{
		Vec3 euler;
		float sy = columns[0][2];
		if (sy < (1.0f - CMP_EPSILON)) {
			if (sy > -(1.0f - CMP_EPSILON)) {
				// is this a pure Y rotation?
				if (columns[1][0] == 0.0 && columns[0][1] == 0.0 && columns[1][2] == 0 && columns[2][1] == 0 && columns[1][1] == 1) {
					// return the simplest form (human friendlier in editor and scripts)
					euler.x = 0.0f;
					euler.y = atan2(columns[0][2], columns[0][0]);
					euler.z = 0.0f;
				}
				else {
					euler.x = std::atan2(-columns[1][2], columns[2][2]);
					euler.y = std::asin(sy);
					euler.z = std::atan2(-columns[0][1], columns[0][0]);
				}
			}
			else {
				euler.x = std::atan2(columns[2][1], columns[1][1]);
				euler.y = -PI / 2.0f;
				euler.z = 0.0f;
			}
		}
		else {
			euler.x = std::atan2(columns[2][1], columns[1][1]);
			euler.y = PI / 2.0f;
			euler.z = 0.0f;
		}
		return euler;
	}

	Vec3 Mat3::GetEulerYXZ() const
	{
		Vec3 euler;

		float m12 = columns[1][2];

		if (m12 < (1 - CMP_EPSILON)) {
			if (m12 > -(1 - CMP_EPSILON)) {
				// is this a pure X rotation?
				if (columns[1][0] == 0 && columns[0][1] == 0 && columns[0][2] == 0 && columns[2][0] == 0 && columns[0][0] == 1) {
					// return the simplest form (human friendlier in editor and scripts)
					euler.x = std::atan2(-m12, columns[1][1]);
					euler.y = 0;
					euler.z = 0;
				}
				else {
					euler.x = std::asin(-m12);
					euler.y = std::atan2(columns[0][2], columns[2][2]);
					euler.z = std::atan2(columns[1][0], columns[1][1]);
				}
			}
			else { // m12 == -1
				euler.x = PI * 0.5f;
				euler.y = atan2(columns[0][1], columns[0][0]);
				euler.z = 0;
			}
		}
		else { // m12 == 1
			euler.x = -PI * 0.5f;
			euler.y = -atan2(columns[0][1], columns[0][0]);
			euler.z = 0;
		}

		return euler;
	}

	Math::Mat3 Mat3::Rotated(const Vec3& euler) const
	{
		return Mat3(euler) * (*this);
	}

	void Mat3::Rotate(const Vec3& euler)
	{
		*this = Rotated(euler);
	}

	void Mat3::SetQuat(const Quat& quat)
	{
		float d = quat.LengthSquared();
		float s = 2.0f / d;
		float xs = quat.x * s, ys = quat.y * s, zs = quat.z * s;
		float wx = quat.w * xs, wy = quat.w * ys, wz = quat.w * zs;
		float xx = quat.x * xs, xy = quat.x * ys, xz = quat.x * zs;
		float yy = quat.y * ys, yz = quat.y * zs, zz = quat.z * zs;
		Set(1.0f - (yy + zz), xy - wz, xz + wy,
			xy + wz, 1.0f - (xx + zz), yz - wx,
			xz - wy, yz + wx, 1.0f - (xx + yy));
	}
}