#pragma once

#include "Elysium/Math/Mat4.h"

namespace Elysium
{
	enum class ProjectionType : unsigned char
	{
		Orthographic = 0, Perspective
	};

	class Camera
	{
	public:
		Camera() = default;

		Camera(const Math::Mat4& projection) 
			: m_projection(projection)
		{
		}

		virtual ~Camera() = default;
	public:
		inline const Math::Mat4& GetProjection() const { return m_projection; }
	protected:
		Math::Mat4 m_projection = Math::Mat4(1.0f);
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera();
		virtual ~OrthographicCamera() = default;
	public:
		void SetPosition(const Math::Vec2& position);
		void SetProperties(float aspectRatio, float size);
	public:
		inline const Math::Mat4& GetView() const { return m_view; }
		inline const Math::Vec2& GetPosition() const { return m_position; }
	private:
		void SetProjection(float horizontal, float vertical);
		void RecalculateViewMatrix();
	private:
		Math::Mat4 m_view;
		Math::Vec2 m_position;

		float m_aspectRatio;
		float m_size;
	};
}