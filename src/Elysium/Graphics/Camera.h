#pragma once

#include "Elysium/Math/Mat4.h"

namespace Elysium
{
	/// <summary>
	/// Enum representing a camera projection type.
	/// </summary>
	enum class ProjectionType : unsigned char
	{
		Orthographic = 0, Perspective
	};

	/// <summary>
	/// Class representing a viewing camera.
	/// </summary>
	class Camera
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		Camera() = default;

		/// <summary>
		/// Constructor initializing a Camera.
		/// </summary>
		/// <param name="projection"></param>
		Camera(const Math::Mat4& projection) 
			: m_projection(projection)
		{
		}

		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~Camera() = default;
	public:
		/// <summary>
		/// Retrieves the projection matrix.
		/// </summary>
		/// <returns>The projection matrix</returns>
		inline const Math::Mat4& GetProjection() const { return m_projection; }
	protected:
		Math::Mat4 m_projection = Math::Mat4(1.0f);
	};

	/// <summary>
	/// Class representing an orthographic viewing camera.
	/// </summary>
	class OrthographicCamera : public Camera
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		OrthographicCamera();

		/// <summary>
		/// Default destructor.
		/// </summary>
		virtual ~OrthographicCamera() = default;
	public:
		/// <summary>
		/// Sets the position of the camera.
		/// </summary>
		/// <param name="position">The position to set</param>
		void SetPosition(const Math::Vec2& position);
		
		/// <summary>
		/// Sets the camera properties.
		/// </summary>
		/// <param name="aspectRatio">The aspect ratio</param>
		/// <param name="size">The zoom size</param>
		void SetProperties(float aspectRatio, float size);
	public:
		/// <summary>
		/// Retrieves the view matrix.
		/// </summary>
		/// <returns>The view matrix</returns>
		inline const Math::Mat4& GetView() const { return m_view; }

		/// <summary>
		/// Retrieves the position of the camera.
		/// </summary>
		/// <returns>The position</returns>
		inline const Math::Vec2& GetPosition() const { return m_position; }
	private:
		/// <summary>
		/// Sets the projection of the camera
		/// </summary>
		/// <param name="horizontal">The horizontal size</param>
		/// <param name="vertical">The vertical size</param>
		void SetProjection(float horizontal, float vertical);

		/// <summary>
		/// Helper method that recalculates the view matrix.
		/// </summary>
		void RecalculateViewMatrix();
	private:
		Math::Mat4 m_view;
		Math::Vec2 m_position;

		float m_aspectRatio;
		float m_size;
	};
}