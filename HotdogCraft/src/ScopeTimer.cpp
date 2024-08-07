#include <GLFW/glfw3.h>
#include <ScopeTimer.h>

namespace HotdogCraft
{
	TimedScope::TimedScope(ScopeTimer& timer, double startTime)
		: timer(timer)
		, startTime(startTime)
	{
	}

	TimedScope::~TimedScope()
	{
		timer.addTime(glfwGetTime() - startTime);
	}

	ScopeTimer::ScopeTimer(int size)
		: maxHistorySize(size)
	{
	}

	TimedScope ScopeTimer::time()
	{
		return TimedScope(*this, glfwGetTime());
	}

	double ScopeTimer::addTime(double t)
	{
		if (history.size() == maxHistorySize)
			history.pop_back();
		history.push_front(t);
		return t;
	}

	double ScopeTimer::getAvg()
	{
		if (history.empty())
			return 0.0;

		double sum = 0.0;
		for (double t : history)
			sum += t;
		return sum / history.size();
	}
}
