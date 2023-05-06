#include "elysium_pch.h"
#include "CoreUniformBuffers.h"

#include "Elysium/Core/Bits.h"
#include "Elysium/Graphics/Constants.h"

namespace Elysium
{
	Unique<CoreUniformBuffers::DataStructs> CoreUniformBuffers::s_data = nullptr;
	Unique<CoreUniformBuffers::Buffers> CoreUniformBuffers::s_buffers = nullptr;

	void CoreUniformBuffers::Initialize()
	{
		s_data = CreateUnique<CoreUniformBuffers::DataStructs>();
		s_buffers = CreateUnique<CoreUniformBuffers::Buffers>();

		s_buffers->m_cameraUniform			= UniformBuffer::Create(sizeof(CameraData),			UNIFORM_SLOT_CAMERA);
		s_buffers->m_timeUniform			= UniformBuffer::Create(sizeof(TimeData),			UNIFORM_SLOT_TIME);
		s_buffers->m_postprocessUniform		= UniformBuffer::Create(sizeof(PostProcessData),	UNIFORM_SLOT_POST_PROCESSING);
	}

	CameraData& CoreUniformBuffers::GetCameraDataRef()
	{
		BIT_SET(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_CAMERA);
		return s_data->m_cameraData;
	}

	void CoreUniformBuffers::SetCameraData(const CameraData& data)
	{
		BIT_SET(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_CAMERA);
		s_data->m_cameraData = data;
	}

	TimeData& CoreUniformBuffers::GetTimeDataRef()
	{
		BIT_SET(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_TIME);
		return s_data->m_timeData;
	}

	void CoreUniformBuffers::SetTimeData(const TimeData& data)
	{
		BIT_SET(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_TIME);
		s_data->m_timeData;
	}

	PostProcessData& CoreUniformBuffers::GetPostProcessDataRef()
	{
		BIT_SET(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_POST_PROCESSING);
		return s_data->m_postprocessData;
	}

	void CoreUniformBuffers::SetPostProcessData(const PostProcessData& data)
	{
		BIT_SET(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_POST_PROCESSING);
		s_data->m_postprocessData = data;
	}

	void CoreUniformBuffers::UploadDirtyData()
	{
		if (BIT_CHECK(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_CAMERA))
			s_buffers->m_cameraUniform->SetData(&s_data->m_cameraData, sizeof(CameraData));

		if (BIT_CHECK(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_TIME))
			s_buffers->m_timeUniform->SetData(&s_data->m_timeData, sizeof(TimeData));

		if (BIT_CHECK(s_buffers->m_dataDirtyFlags, UNIFORM_SLOT_POST_PROCESSING))
			s_buffers->m_postprocessUniform->SetData(&s_data->m_postprocessData, sizeof(PostProcessData));

		s_buffers->m_dataDirtyFlags = 0;
	}
}
