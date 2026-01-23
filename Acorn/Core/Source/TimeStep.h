#pragma once

#include <GLFW/glfw3.h>

namespace Crimson {

	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }
		TimeStep operator=(float time) { m_Time = time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds () const { return m_Time * 1000.0f; }

		inline static float GetTime() 
		{
			return static_cast<float>(glfwGetTime());
		}

	private:
		float m_Time;
	};
}