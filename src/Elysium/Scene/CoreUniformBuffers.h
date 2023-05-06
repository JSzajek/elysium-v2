#pragma once

#include "Elysium/Scene/CoreUniformBuffersDefines.h"

#include "Elysium/Core/Memory.h"
#include "Elysium/Graphics/UniformBuffer.h"

namespace Elysium
{
	class CoreUniformBuffers
	{
	private:
		struct DataStructs
		{
		public:
			CameraData m_cameraData;
			TimeData m_timeData;
			PostProcessData m_postprocessData;
		};
		static Unique<DataStructs> s_data;

		struct Buffers
		{
		public:
			uint32_t m_dataDirtyFlags;

			Shared<UniformBuffer> m_cameraUniform;
			Shared<UniformBuffer> m_timeUniform;
			Shared<UniformBuffer> m_postprocessUniform;
		};
		static Unique<Buffers> s_buffers;
	public:
		static void Initialize();

		static CameraData& GetCameraDataRef();
		static void SetCameraData(const CameraData& data);

		static TimeData& GetTimeDataRef();
		static void SetTimeData(const TimeData& data);

		static PostProcessData& GetPostProcessDataRef();
		static void SetPostProcessData(const PostProcessData& data);

		static void UploadDirtyData();
	};
}
