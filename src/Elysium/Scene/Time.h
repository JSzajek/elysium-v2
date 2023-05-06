#pragma once

namespace Elysium
{
	class DeltaTime
	{
	private:
		float m_time;
	public:
		DeltaTime(float time = 0.0f)
			: m_time(time)
		{
		}

		operator float() const { return m_time; }

		float GetSeconds() const { return m_time; }
		float GetMilliseconds() const { return m_time * 1000.0f; }
	};

	class Time
	{
	private:
		friend class Application;
	private:
		static float s_totalTime;
		static DeltaTime s_deltaTime;
	public:
		inline static float TotalTime() { return s_totalTime; }
		inline static DeltaTime DeltaTime() { return s_deltaTime; }
	protected:
		inline static void UpdateTime(float nowTime) 
		{
			s_deltaTime = nowTime - s_totalTime; 
			s_totalTime = nowTime;
		}
	};
}
