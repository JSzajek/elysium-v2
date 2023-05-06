#pragma once

#include "MathsUtils.h"

#include "Vec3.h"
#include "Quat.h"

namespace Elysium::Math
{
	struct Mat3
	{
	public:
		union
		{
			float data[3 * 3];
			Vec3 columns[3];
		};
	public:
		Mat3();
		Mat3(const Quat& p_quat);
		Mat3(const Mat3& other);
		Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2);
		Mat3(float v00, float v01, float v02,
			 float v10, float v11, float v12,
			 float v20, float v21, float v22);

		void operator=(const Mat3& other);
		inline Mat3 operator*(const Mat3& matrix) const;

		// transposed dot products
		inline float tdotx(const Vec3& v) const {
			return columns[0][0] * v[0] + columns[1][0] * v[1] + columns[2][0] * v[2];
		}
		inline float tdoty(const Vec3& v) const {
			return columns[0][1] * v[0] + columns[1][1] * v[1] + columns[2][1] * v[2];
		}
		inline float tdotz(const Vec3& v) const {
			return columns[0][2] * v[0] + columns[1][2] * v[1] + columns[2][2] * v[2];
		}

		inline Vec3 GetAxis(int axis) const 
		{
			// get actual basis axis (elements is transposed for performance)
			return Vec3(columns[0][axis], columns[1][axis], columns[2][axis]);
		}

		inline void SetAxis(int axis, const Vec3& value) 
		{
			// get actual basis axis (elements is transposed for performance)
			columns[0][axis] = value.x;
			columns[1][axis] = value.y;
			columns[2][axis] = value.z;
		}

		void Orthonormalize();
		Mat3 Orthonormalized() const;
		float Determinant() const;

		const Mat3 Inverse(bool* success = nullptr) const;
		void Transpose();

		void Scale(const Vec3& scale);

		Vec3 GetRotationEuler() const;
		Vec3 GetEulerXYZ() const;
		Vec3 GetEulerYXZ() const;

		Vec3 GetEuler() const { return GetEulerXYZ(); }

		Math::Mat3 Rotated(const Vec3& euler) const;
		void Rotate(const Vec3& euler);
	private:
		void SetQuat(const Quat& quat);

		inline void Set(float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz) 
		{
			columns[0][0] = xx;
			columns[0][1] = xy;
			columns[0][2] = xz;
			columns[1][0] = yx;
			columns[1][1] = yy;
			columns[1][2] = yz;
			columns[2][0] = zx;
			columns[2][1] = zy;
			columns[2][2] = zz;
		}
	};
}