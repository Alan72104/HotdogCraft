#pragma once

namespace HotdogCraft
{
	class HotdogCraft;

	class GameRenderer
	{
	public:
		GameRenderer(HotdogCraft& glCraft);

	private:
		HotdogCraft& glCraft;
	};
}
