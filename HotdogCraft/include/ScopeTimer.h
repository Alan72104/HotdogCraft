#pragma once

#include <deque>

namespace HotdogCraft
{
	class ScopeTimer;

	struct TimedScope
	{
	public:
		~TimedScope();

	private:
		friend class ScopeTimer;

		TimedScope(ScopeTimer& timer, double startTime);

		ScopeTimer& timer;
		double startTime;
	};

	class ScopeTimer
	{
	public:
		ScopeTimer(int size);
		TimedScope time();
		double addTime(double t);
		double getAvg();

	private:
		const int maxHistorySize;
		std::deque<double> history{};
	};
}