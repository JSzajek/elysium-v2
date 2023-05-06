#pragma once

#include "Elysium/Core/Memory.h"

#include "Elysium/Math/Maths.h"

#include "Elysium/Graphics/Texture.h"

namespace Elysium
{
	struct RectTransformComponent
	{
	public:
		RectTransformComponent();
		RectTransformComponent(const RectTransformComponent& copy) = default;
	public:
		void SetTranslation(const Math::Vec2& translation);
		void SetDimensions(const Math::Vec2& dimensions);
		void SetRotation(float radians);
		void SetRotationDegrees(float degrees);
		void SetScale(const Math::Vec2& scale);
		void SetPivotOffset(const Math::Vec2& offset);
	public:
		inline Math::Vec2 GetTranslation() const { return m_translation; }
		inline Math::Vec2 GetDimensions() const { return m_dimensions; }
		inline float GetRotation() const { return m_rotation_rad; }
		inline float GetRotationDegrees() const { return Math::ToDegrees(m_rotation_rad); }
		inline Math::Vec2 GetScale() const { return m_scale; }
		inline Math::Vec2 GetPivotOffset() const { return m_pivotOffset; }

		inline Math::Mat4 GetTransform() const { return m_transform; }
		inline Math::Vec2 GetCenter() const { return m_center; }
	private:
		void UpdateTransformMatrix();
	private:
		Math::Vec2 m_translation;
		Math::Vec2 m_dimensions;

		float m_rotation_rad; /* Radians */

		Math::Vec2 m_scale;
		Math::Vec2 m_pivotOffset;

		Math::Mat4 m_transform;
		Math::Vec2 m_center;
	};

	struct SpriteComponent
	{
	public:
		Shared<Texture2D> Texture = nullptr;
		Math::Vec4 Color = Math::Vec4::One;

		int32_t ZOrder = 0;
	public:
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& copy) = default;
	};

	struct PanelComponent
	{
	};

	struct LabelComponent
	{
	};
}