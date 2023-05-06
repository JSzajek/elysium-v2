#include "elysium_pch.h"
#include "Elysium/Scene/2DComponents.h"

#include "Elysium/Renderer/RendererDefines.h"

namespace Elysium
{
	RectTransformComponent::RectTransformComponent()
		: m_translation(0), m_dimensions(0), m_rotation_rad(0), 
		m_scale(1), m_pivotOffset(0), m_transform(1)
	{
	}

	void RectTransformComponent::SetTranslation(const Math::Vec2& translation)
	{
		m_translation = translation;
		UpdateTransformMatrix();
	}

	void RectTransformComponent::SetDimensions(const Math::Vec2& dimensions)
	{
		m_dimensions = dimensions;
		UpdateTransformMatrix();
	}

	void RectTransformComponent::SetRotation(float rotation)
	{
		m_rotation_rad = rotation;
		UpdateTransformMatrix();
	}

	void RectTransformComponent::SetRotationDegrees(float degrees)
	{
		m_rotation_rad = Math::ToRadians(degrees);
		UpdateTransformMatrix();
	}

	void RectTransformComponent::SetScale(const Math::Vec2& scale)
	{
		m_scale = scale;
		UpdateTransformMatrix();
	}

	void RectTransformComponent::SetPivotOffset(const Math::Vec2& offset)
	{
		m_pivotOffset = offset;
		UpdateTransformMatrix();
	}

	void RectTransformComponent::UpdateTransformMatrix()
	{
		m_transform = Math::Mat4::Identity;
		m_transform = m_transform.Translate(m_translation + m_pivotOffset);
		m_transform = m_transform.Rotate(m_rotation_rad, Math::Vec3::Z_Axis);
		m_transform = m_transform.Translate(-m_pivotOffset);
		m_transform = m_transform.Scale(Math::Vec3(m_dimensions * m_scale, 0.0f));

		// TODO:: Move to Bounding Box Component?
		const Math::Vec3 bounding_avg = ((m_transform * s_defaultQuadCoords[0]) + (m_transform * s_defaultQuadCoords[2])) * 0.5f;
		m_center.x = bounding_avg.x;
		m_center.y = bounding_avg.y;
	}

}