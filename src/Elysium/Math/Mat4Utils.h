#pragma once

#include "Mat4.h"
#include "Mat3.h"
#include "Quat.h"
#include "Vec3.h"

namespace Elysium::Math
{
	class Mat4Utils
	{
	public:
		static bool DecomposeTransformMatrix(const Math::Mat4& transform, Math::Vec3& translation, Math::Vec3& rotation, Math::Vec3& scale)
		{
			translation.x = transform.columns[3][0];
			translation.y = transform.columns[3][1];
			translation.z = transform.columns[3][2];
		
			auto colX = Math::Vec3(transform.columns[0]);
			auto colY = Math::Vec3(transform.columns[1]);
			auto colZ = Math::Vec3(transform.columns[2]);
			
			scale.x = colX.Length();
			scale.y = colY.Length();
			scale.z = colZ.Length();

			colX.Normalize();
			colY.Normalize();
			colZ.Normalize();

			Math::Mat3 rotationMatrix(colX.x / scale.x, colY.x / scale.y, colZ.x / scale.z,
									  colX.y / scale.x, colY.y / scale.y, colZ.y / scale.z,
									  colX.z / scale.x, colY.z / scale.y, colZ.z / scale.z);

			rotation = rotationMatrix.GetRotationEuler();
			
			return true;

		}

		static bool ViewMatrix(float pitch, float yaw, const Math::Vec3& position, Math::Mat4* result)
		{
			result->SetIdentity();

			result->Rotate(pitch, Math::Vec3::X_Axis);
			result->Rotate(yaw, Math::Vec3::Y_Axis);
			result->Translate(position);
			
			return true;
		}

		static Math::Mat4 TransformToRotationMatrix(const Math::Mat4& transform)
		{
			// Find Scale
			auto colX = Math::Vec3(transform.columns[0]);
			auto colY = Math::Vec3(transform.columns[1]);
			auto colZ = Math::Vec3(transform.columns[2]);
			
			auto scaleX = colX.Length();
			auto scaleY = colY.Length();
			auto scaleZ = colZ.Length();

			colX.Normalize();
			colY.Normalize();
			colZ.Normalize();

			// Create Rotation only matrix
			return Math::Mat4(colX.x / scaleX, colX.y / scaleX, colX.z / scaleX, 0,
							  colY.x / scaleY, colY.y / scaleY, colY.z / scaleY, 0,
							  colZ.x / scaleZ, colZ.y / scaleZ, colZ.z / scaleZ, 0,
							  0, 0, 0, 1);
		}
	};
}