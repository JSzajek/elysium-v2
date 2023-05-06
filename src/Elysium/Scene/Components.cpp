#include "elysium_pch.h"
#include "Elysium/Scene/Components.h"

namespace Elysium
{
	TransformComponent::TransformComponent()
		: Translation(0), Rotation(0), Scale(1)
	{
	}

	Elysium::Math::Mat4 TransformComponent::GetTransform() const
	{
		Math::Mat4 result(1);
		result.Translate(Translation);
		result.Rotate(Rotation.x, Math::Vec3::X_Axis);
		result.Rotate(Rotation.y, Math::Vec3::Y_Axis);
		result.Rotate(Rotation.z, Math::Vec3::Z_Axis);
		result.Scale(Scale);
		return result;
	}
}