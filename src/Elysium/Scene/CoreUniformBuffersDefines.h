#pragma once

#include "Elysium/Math/Vec4.h"
#include "Elysium/Math/Mat4.h"

namespace Elysium
{
	struct UniformDataStruct
	{
		//public:
		//	bool m_dirtyFlag = false;
	};

	struct CameraData : public UniformDataStruct
	{
	public:
		Math::Mat4 m_viewMatrix;
		Math::Mat4 m_orthoViewMatrix;
		Math::Mat4 m_projectionMatrix;
		Math::Mat4 m_orthoProjectionMatrix;
		Math::Vec4 m_cameraPosition;
		Math::Vec4 m_viewport;
	public:
		CameraData() = default;
	};

	struct TimeData : public UniformDataStruct
	{
	public:
		float m_time = 0.f;
		float m_deltaTime = 0.f;
	public:
		TimeData() = default;
	};

	struct PostProcessData : public UniformDataStruct
	{
	public:
		Math::Vec4 m_gammaAdjustment;
		float m_exposure = 1.1f;
		int m_samplingType = 0;
		int m_samplingLayer = 0;
	public:
		PostProcessData() = default;
	};
}