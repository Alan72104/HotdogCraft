#pragma once

namespace HotdogCraft
{
	class Timer
	{
	public:
		Timer(double threshold);

		double getThreshold();
		void setThreshold(double t);
		double elapsedTime();
		void reset();
		bool isElapsed();
		bool checkElapsedAndReset();

	private:
		double threshold;
		double startTime{ 0 };
	};
}