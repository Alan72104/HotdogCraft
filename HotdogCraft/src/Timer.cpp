#include <GLFW/glfw3.h>

#include <Timer.h>

namespace HotdogCraft
{
	Timer::Timer(double threshold)
		: threshold(threshold)
	{
	}

	double Timer::getThreshold()
	{
		return threshold;
	}

	void Timer::setThreshold(double t)
	{
		threshold = t;
	}

	double Timer::elapsedTime()
	{
		return glfwGetTime() - startTime;
	}

	void Timer::reset()
	{
		startTime = glfwGetTime();
	}

	bool Timer::isElapsed()
	{
		return glfwGetTime() - startTime >= threshold;
	}

	bool Timer::checkElapsedAndReset()
	{
		if (isElapsed())
		{
			reset();
			return true;
		}
		return false;
	}
}