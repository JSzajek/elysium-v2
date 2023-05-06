#include "elysium_pch.h"

#include "Mat4.h"

namespace Elysium::Math
{
	const Mat4 Mat4::Identity = Mat4(1.0f);

	Mat4::Mat4()
	{
		memset(data, 0, 4 * 4 * sizeof(float));
	}

	Mat4::Mat4(float diagonal)
	{
		memset(data, 0, 4 * 4 * sizeof(float));
		SetDiagonal(diagonal);
	}

	Mat4::Mat4(const Mat4& other)
	{
		memcpy(data, other.data, 16 * sizeof(float));
	}

	Mat4::Mat4(const Vec3& translation, const Quat& rotation, const Vec3& scale)
	{
		// Calc Coefficients
		auto xx = rotation.x * rotation.x;	auto yy = rotation.y * rotation.y;	auto zz = rotation.z * rotation.z;
		auto xy = rotation.x * rotation.y;	auto yz = rotation.y * rotation.z;	auto zw = rotation.z * rotation.w;
		auto xz = rotation.x * rotation.z;	auto yw = rotation.y * rotation.w;
		auto xw = rotation.x * rotation.w;

		columns[0][0] = (1.0f) - (2.0f) * (yy + zz) * scale.x;	//rot00 * xScale
		columns[1][0] = (2.0f) * (xy - zw) * scale.x;			//rot10 * xScale
		columns[2][0] = (2.0f) * (xz + yw) * scale.x;			//rot20 * xScale
		columns[3][0] = translation.x;

		columns[0][1] = (2.0f) * (xy + zw) * scale.y;			//rot01 * yScale
		columns[1][1] = (1.0f) - (2.0f) * (xx + zz) * scale.y;	//rot11 * yScale
		columns[2][1] = (2.0f) * (yz - xw) * scale.y;			//rot21 * yScale
		columns[3][1] = translation.y;

		columns[0][2] = (2.0f) * (xz - yw) * scale.z;			//rot02 * zScale
		columns[1][2] = (2.0f) * (yz + xw) * scale.z;			//rot12 * zScale
		columns[2][2] = (1.0f) - (2.0f) * (xx + yy) * scale.z;	//rot22 * zScale
		columns[3][2] = translation.z;

		columns[0][3] = columns[1][3] = columns[2][3] = 0.0f;
		columns[3][3] = 1.0f;
	}

	Mat4::Mat4(float v00, float v01, float v02, float v03,
		       float v10, float v11, float v12, float v13,
		       float v20, float v21, float v22, float v23,
		       float v30, float v31, float v32, float v33)
	{
		columns[0][0] = v00;
		columns[0][1] = v01;
		columns[0][2] = v02;
		columns[0][3] = v03;

		columns[1][0] = v10;
		columns[1][1] = v11;
		columns[1][2] = v12;
		columns[1][3] = v13;

		columns[2][0] = v20;
		columns[2][1] = v21;
		columns[2][2] = v22;
		columns[2][3] = v23;

		columns[3][0] = v30;
		columns[3][1] = v31;
		columns[3][2] = v32;
		columns[3][3] = v33;
	}

	Mat4::Mat4(const Vec4& vals)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				data[4 * i + j] = vals[i] * vals[j];
			}
		}
	}

	void Mat4::operator=(const Mat4& other)
	{
		memcpy(data, other.data, 16 * sizeof(float));
	}

	void Mat4::SetIdentity()
	{
		memset(data, 0, 4 * 4 * sizeof(float));
		SetDiagonal(1);
	}

	Mat4& Mat4::Multiply(const Mat4& other)
	{
		float result[4 * 4];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0;
				for (int d = 0; d < 4; d++)
				{
					sum += data[x + d * 4] * other.data[d + y * 4];
				}
				result[x + y * 4] = sum;
			}
		}
		memcpy(data, result, 4 * 4 * sizeof(float));
		return *this;
	}

	Vec4 Mat4::Multiply(const Vec4& other) const
	{
		return Vec4(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
			columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
		);
	}

	Vec3 Mat4::Multiply(const Vec3& other) const
	{
		return Vec3(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
		);
	}

	Vec4 operator*(const Mat4& left, const Vec4& right)
	{
		return left.Multiply(right);
	}

	Vec3 operator*(const Mat4& left, const Vec3& right)
	{
		return left.Multiply(right);
	}

	/// <summary>
	/// Multiplication operator override.
	/// </summary>
	/// <param name="other">The other Mat4 to multiply</param>
	/// <returns>The multiplied Mat4</returns>
	Mat4 operator*(Mat4 left, const Mat4& right)
	{
		return left.Multiply(right);
	}

	/// <summary>
	/// Multiplication operator override.
	/// </summary>
	/// <param name="other">The other Mat4 to multiply</param>
	/// <returns>The multiplied Mat4</returns>
	Mat4& Mat4::operator*=(const Mat4& other)
	{
		return Multiply(other);
	}

	Mat4 Mat4::operator+(const Mat4& r_val) const
	{
		Mat4 result;
		for (int i = 0; i < 16; ++i) {
			result.data[i] = data[i] + r_val.data[i];
		}
		return result;
	}

	void Mat4::operator+=(const Mat4& r_val)
	{
		for (int i = 0; i < 16; ++i) {
			data[i] += r_val.data[i];
		}
	}

	Mat4& Mat4::Translate(const Vec3& other)
	{
		Mat4 translationMatrix = TranslationMatrix(other);
		return Multiply(translationMatrix);
	}

	Mat4& Mat4::Translate(const Vec2& other)
	{
		Mat4 translationMatrix = TranslationMatrix(other);
		return Multiply(translationMatrix);
	}

	Mat4& Mat4::Rotate(float radians, const Vec3& other)
	{
		Multiply(RotationMatrix(radians, other));
		return *this;
	}

	Mat4& Mat4::Rotate(const Quat& quat)
	{
		Multiply(RotationMatrix(quat));
		return *this;
	}

	Mat4& Mat4::Scale(const Vec3& other)
	{
		Multiply(ScaleMatrix(other));
		return *this;
	}

	Mat4& Mat4::Scale(float scale)
	{
		Multiply(ScaleMatrix(scale));
		return *this;
	}

	const Mat4 Mat4::Inverse(bool* success) const
	{
		Mat4 inverse(0);

		auto m00 = columns[0][0];
		auto m01 = columns[0][1];
		auto m02 = columns[0][2];
		auto m03 = columns[0][3];
		
		auto m10 = columns[1][0];
		auto m11 = columns[1][1];
		auto m12 = columns[1][2];
		auto m13 = columns[1][3];
		
		auto m20 = columns[2][0];
		auto m21 = columns[2][1];
		auto m22 = columns[2][2];
		auto m23 = columns[2][3];

		auto m30 = columns[3][0];
		auto m31 = columns[3][1];
		auto m32 = columns[3][2];
		auto m33 = columns[3][3];

		auto A2323 = m22 * m33 - m23 * m32;
		auto A1323 = m21 * m33 - m23 * m31;
		auto A1223 = m21 * m32 - m22 * m31;
		auto A0323 = m20 * m33 - m23 * m30;
		auto A0223 = m20 * m32 - m22 * m30;
		auto A0123 = m20 * m31 - m21 * m30;
		auto A2313 = m12 * m33 - m13 * m32;
		auto A1313 = m11 * m33 - m13 * m31;
		auto A1213 = m11 * m32 - m12 * m31;
		auto A2312 = m12 * m23 - m13 * m22;
		auto A1312 = m11 * m23 - m13 * m21;
		auto A1212 = m11 * m22 - m12 * m21;
		auto A0313 = m10 * m33 - m13 * m30;
		auto A0213 = m10 * m32 - m12 * m30;
		auto A0312 = m10 * m23 - m13 * m20;
		auto A0212 = m10 * m22 - m12 * m20;
		auto A0113 = m10 * m31 - m11 * m30;
		auto A0112 = m10 * m21 - m11 * m20;

		auto det = m00 * (m11 * A2323 - m12 * A1323 + m13 * A1223)
				 - m01 * (m10 * A2323 - m12 * A0323 + m13 * A0223)
				 + m02 * (m10 * A1323 - m11 * A0323 + m13 * A0123)
				 - m03 * (m10 * A1223 - m11 * A0223 + m12 * A0123);

		if (std::fabs(det) <= CMP_EPSILON)
		{
			if (success)
			{
				*success = false;
			}
			return *this;
		}
		else
		{
			det = 1 / det;
			if (success)
			{
				*success = true;
			}
		}

		return Mat4(
		   det *  (m11 * A2323 - m12 * A1323 + m13 * A1223),
		   det * -(m01 * A2323 - m02 * A1323 + m03 * A1223),
		   det *  (m01 * A2313 - m02 * A1313 + m03 * A1213),
		   det * -(m01 * A2312 - m02 * A1312 + m03 * A1212),
		   det * -(m10 * A2323 - m12 * A0323 + m13 * A0223),
		   det *  (m00 * A2323 - m02 * A0323 + m03 * A0223),
		   det * -(m00 * A2313 - m02 * A0313 + m03 * A0213),
		   det *  (m00 * A2312 - m02 * A0312 + m03 * A0212),
		   det *  (m10 * A1323 - m11 * A0323 + m13 * A0123),
		   det * -(m00 * A1323 - m01 * A0323 + m03 * A0123),
		   det *  (m00 * A1313 - m01 * A0313 + m03 * A0113),
		   det * -(m00 * A1312 - m01 * A0312 + m03 * A0112),
		   det * -(m10 * A1223 - m11 * A0223 + m12 * A0123),
		   det *  (m00 * A1223 - m01 * A0223 + m02 * A0123),
		   det * -(m00 * A1213 - m01 * A0213 + m02 * A0113),
		   det *  (m00 * A1212 - m01 * A0212 + m02 * A0112)
		);
	}

	void Mat4::Transpose()
	{
		float result[4 * 4];
		result[0]  = data[0];
		result[1]  = data[4];
		result[2]  = data[8];
		result[3]  = data[12];
		result[4]  = data[1];
		result[5]  = data[5];
		result[6]  = data[9];
		result[7]  = data[13];
		result[8]  = data[2];
		result[9]  = data[6];
		result[10] = data[10];
		result[11] = data[14];
		result[12] = data[3];
		result[13] = data[7];
		result[14] = data[11];
		result[15] = data[15];
		memcpy(data, result, 4 * 4 * sizeof(float));
	}

	Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float _near, float _far)
	{
		Mat4 result;
		result.data[0 + 0 * 4] = 2.0f / (right - left);
		result.data[1 + 1 * 4] = 2.0f / (top - bottom);
		result.data[2 + 2 * 4] = 2.0f / (_far - _near);

		result.data[0 + 3 * 4] = -((right + left) / (right - left));
		result.data[1 + 3 * 4] = -((top + bottom) / (top - bottom));
		result.data[2 + 3 * 4] = -((_far + _near) / (_far - _near));
		result.data[3 + 3 * 4] = 1;
		return result;
	}

	Mat4 Mat4::Perspective(float aspectRatio, float fov, float _near, float _far)
	{
		Mat4 result;
		float ymax, xmax;
		ymax = _near * tanf(fov);
		xmax = ymax * aspectRatio;
		Frustum(-xmax, xmax, -ymax, ymax, _near, _far, result.data);
		return result;
	}

	static float Dot(const float* a, const float* b)
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	}

	static void Normalize(const float* a, float* r)
	{
		float il = 1.f / (sqrtf(Dot(a, a)) + FLT_EPSILON);
		r[0] = a[0] * il;
		r[1] = a[1] * il;
		r[2] = a[2] * il;
	}

	static void Cross(const float* a, const float* b, float* r)
	{
		r[0] = a[1] * b[2] - a[2] * b[1];
		r[1] = a[2] * b[0] - a[0] * b[2];
		r[2] = a[0] * b[1] - a[1] * b[0];
	}

	Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& target, const Vec3& upAxis)
	{
		Mat4 result;
		Vec3 X, Y, Z, tmp;

		tmp[0] = eye[0] - target[0];
		tmp[1] = eye[1] - target[1];
		tmp[2] = eye[2] - target[2];
		
		Normalize(tmp.m_data, Z.m_data);
		Normalize(upAxis.m_data, Y.m_data);

		Cross(Y.m_data, Z.m_data, tmp.m_data);
		Normalize(tmp.m_data, X.m_data);

		Cross(Z.m_data, X.m_data, tmp.m_data);
		Normalize(tmp.m_data, Y.m_data);

		result.data[0] = X[0];
		result.data[1] = Y[0];
		result.data[2] = Z[0];
		result.data[3] = 0.0f;
		result.data[4] = X[1];
		result.data[5] = Y[1];
		result.data[6] = Z[1];
		result.data[7] = 0.0f;
		result.data[8] = X[2];
		result.data[9] = Y[2];
		result.data[10] = Z[2];
		result.data[11] = 0.0f;
		result.data[12] = -Dot(X.m_data, eye.m_data);
		result.data[13] = -Dot(Y.m_data, eye.m_data);
		result.data[14] = -Dot(Z.m_data, eye.m_data);
		result.data[15] = 1.0f;
		return result;
	}

	Mat4 Mat4::TranslationMatrix(const Vec2& translation)
	{
		Mat4 result(1.0f);

		result.data[0 + 3 * 4] = translation.x;
		result.data[1 + 3 * 4] = translation.y;

		return result;
	}

	Mat4 Mat4::TranslationMatrix(const Vec3& translation)
	{
		Mat4 result(1.0f);

		result.data[0 + 3 * 4] = translation.x;
		result.data[1 + 3 * 4] = translation.y;
		result.data[2 + 3 * 4] = translation.z;
		
		return result;
	}

	Mat4 Mat4::RotationMatrix(float radians, const Vec3& axis)
	{
		Mat4 result(1);
		const float c = cos(radians);
		const float s = sin(radians);

		Vec3 normAxis = Vec3(axis);
		normAxis.Normalize();

		Vec3 temp(axis);
		temp *= (1 - c);

		result.columns[0][0] = c + temp[0] * normAxis[0];
		result.columns[0][1] = temp[0] * normAxis[1] + s * normAxis[2];
		result.columns[0][2] = temp[0] * normAxis[2] - s * normAxis[1];
		
		result.columns[1][0] = temp[1] * normAxis[0] - s * normAxis[2];
		result.columns[1][1] = c + temp[1] * normAxis[1];
		result.columns[1][2] = temp[1] * normAxis[2] + s * normAxis[0];
		
		result.columns[2][0] = temp[2] * normAxis[0] + s * normAxis[1];
		result.columns[2][1] = temp[2] * normAxis[1] - s * normAxis[0];
		result.columns[2][2] = c + temp[2] * normAxis[2];
		return result;
	}

	Mat4 Mat4::RotationMatrix(const Quat& quat)
	{
		// Equations based on https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
		Mat4 result(1);

		// Calc Coefficients
		auto xx = quat.x * quat.x;	auto yy = quat.y * quat.y;	auto zz = quat.z * quat.z;
		auto xy = quat.x * quat.y;	auto yz = quat.y * quat.z;	auto zw = quat.z * quat.w;
		auto xz = quat.x * quat.z;	auto yw = quat.y * quat.w;
		auto xw = quat.x * quat.w;

		result.columns[0][0] = 1.0f - 2.0f * (yy + zz);
		result.columns[0][1] = 2.0f * (xy - zw);
		result.columns[0][2] = 2.0f * (xz + yw);

		result.columns[1][0] = 2.0f * (xy + zw);
		result.columns[1][1] = 1.0f - 2.0f * (xx + zz);
		result.columns[1][2] = 2.0f * (yz - xw);

		result.columns[2][0] = 2.0f * (xz - yw);
		result.columns[2][1] = 2.0f * (yz + xw);
		result.columns[2][2] = 1.0f - 2.0f * (xx + yy);

		return result;
	}

	void Mat4::RotationX(Math::Mat4& output, float radians)
	{
		float cosine = std::cosf(radians);
		float sine = std::sinf(radians);

		output.columns[0][0] = 1.0f;
		output.columns[0][1] = 0.0f;
		output.columns[0][2] = 0.0f;
		output.columns[0][3] = 0.0f;

		output.columns[1][0] = 0.0f;
		output.columns[1][1] = cosine;
		output.columns[1][2] = -sine;
		output.columns[1][3] = 0.0f;

		output.columns[2][0] = 1.0f;
		output.columns[2][1] = sine;
		output.columns[2][2] = cosine;
		output.columns[2][3] = 0.0f;

		output.columns[3][0] = 0.0f;
		output.columns[3][1] = 0.0f;
		output.columns[3][2] = 0.0f;
		output.columns[3][3] = 1.0f;
	}

	void Mat4::RotationY(Math::Mat4 & output, float radians)
	{
		float cosine = std::cosf(radians);
		float sine = std::sinf(radians);

		output.columns[0][0] = cosine;
		output.columns[0][1] = 0.0f;
		output.columns[0][2] = sine;
		output.columns[0][3] = 0.0f;

		output.columns[1][0] = 0.0f;
		output.columns[1][1] = 1.0f;
		output.columns[1][2] = 0.0f;
		output.columns[1][3] = 0.0f;

		output.columns[2][0] = -sine;
		output.columns[2][1] = 0.0f;
		output.columns[2][2] = cosine;
		output.columns[2][3] = 0.0f;

		output.columns[3][0] = 0.0f;
		output.columns[3][1] = 0.0f;
		output.columns[3][2] = 0.0f;
		output.columns[3][3] = 1.0f;
	}

	void Mat4::RotationZ(Math::Mat4 & output, float radians)
	{
		float cosine = std::cosf(radians);
		float sine = std::sinf(radians);

		output.columns[0][0] = cosine;
		output.columns[0][1] = -sine;
		output.columns[0][2] = 0.0f;
		output.columns[0][3] = 0.0f;

		output.columns[1][0] = sine;
		output.columns[1][1] = cosine;
		output.columns[1][2] = 0.0f;
		output.columns[1][3] = 0.0f;

		output.columns[2][0] = 0.0f;
		output.columns[2][1] = 0.0f;
		output.columns[2][2] = 1.0f;
		output.columns[2][3] = 0.0f;

		output.columns[3][0] = 0.0f;
		output.columns[3][1] = 0.0f;
		output.columns[3][2] = 0.0f;
		output.columns[3][3] = 1.0f;
	}

	Mat4 Mat4::ScaleMatrix(float scale)
	{
		Mat4 result(1.0f);

		result.data[0 + 0 * 4] = scale;
		result.data[1 + 1 * 4] = scale;
		result.data[2 + 2 * 4] = scale;
		
		return result;
	}

	Mat4 Mat4::ScaleMatrix(const Vec3& scale)
	{
		Mat4 result(1.0f);

		result.data[0 + 0 * 4] = scale.x;
		result.data[1 + 1 * 4] = scale.y;
		result.data[2 + 2 * 4] = scale.z;

		return result;
	}

	void Mat4::SetDiagonal(float diagonal)
	{
		data[0] = diagonal;
		data[1 + 1 * 4] = diagonal;
		data[2 + 2 * 4] = diagonal;
		data[3 + 3 * 4] = diagonal;
	}

	void Mat4::Frustum(float left, float right, float bottom, float top, float znear, float zfar, float* matrix16)
	{
		const float temp = 2.0f * znear;
		const float temp2 = right - left;
		const float temp3 = top - bottom;
		const float temp4 = zfar - znear;

		matrix16[0] = temp / temp2;
		matrix16[1] = 0.0f;
		matrix16[2] = 0.0f;
		matrix16[3] = 0.0f;
		matrix16[4] = 0.0f;
		matrix16[5] = temp / temp3;
		matrix16[6] = 0.0f;
		matrix16[7] = 0.0f;
		matrix16[8] = (right + left) / temp2;
		matrix16[9] = (top + bottom) / temp3;
		matrix16[10] = (-zfar - znear) / temp4;
		matrix16[11] = -1.0f;
		matrix16[12] = 0.0f;
		matrix16[13] = 0.0f;
		matrix16[14] = (-temp * zfar) / temp4;
		matrix16[15] = 0.0f;
	}
}