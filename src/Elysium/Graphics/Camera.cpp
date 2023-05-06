#include "elysium_pch.h"

#include "Elysium/Graphics/Camera.h"
#include "Elysium/Logging/Instrumentor.h"

namespace Elysium
{
	OrthographicCamera::OrthographicCamera()
		: m_view(1), m_position(0), m_aspectRatio(0), m_size(500)
	{
	}

	void OrthographicCamera::SetPosition(const Math::Vec2& position)
	{
		ELYSIUM_PROFILE_FUNCTION();

		m_position = position;

		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetProperties(float aspectRatio, float size)
	{
		ELYSIUM_PROFILE_FUNCTION();

		m_size = size;
		m_aspectRatio = aspectRatio;

		const float horizontal = m_size * m_aspectRatio * 0.5f;
		const float vertical = m_size * 0.5f;

		SetProjection(horizontal, vertical);
	}

	void OrthographicCamera::SetProjection(float horizontal, float vertical)
	{
		m_projection = Math::Mat4::Orthographic(-horizontal, horizontal, vertical, -vertical, -1000.0f, 1000.0f);
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		auto transform = Math::Mat4(1);
		transform.Translate(m_position);
		
		m_view = transform.Inverse();
	}
}