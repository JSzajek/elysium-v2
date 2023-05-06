#pragma once

#include "Elysium/Core/UUIDs.h"
#include "Elysium/Math/Mat4.h"
#include "Elysium/Math/Vec3.h"

#include <string>

namespace Elysium
{
	struct TagComponent
	{
	public:
		std::string Tag;
	public:
		TagComponent() = default;
		TagComponent(const TagComponent& copy) = default;
		TagComponent(const std::string& tag)
			: Tag(tag)
		{
		}
	};

	struct UUIDComponent
	{
	public:
		UUID Id;
	public:
		UUIDComponent() = default;
		UUIDComponent(const UUIDComponent& copy) = default;
		UUIDComponent(const std::string& str)
			: Id(str)
		{
		}
	};

	struct TransformComponent
	{
	public:
		Math::Vec3 Translation;
		Math::Vec3 Rotation;
		Math::Vec3 Scale;
	public:
		TransformComponent();
		TransformComponent(const TransformComponent& copy) = default;
		TransformComponent(const Math::Vec3& translation)
			: Translation(translation)
		{
		}
	public:
		Math::Mat4 GetTransform() const;
		inline operator Math::Mat4() const { return GetTransform(); }
	};
}