#include <concepts>
#include <string>
#include <type_traits>

namespace HotdogCraft
{
	namespace Utils
	{
		template<typename T>
		concept integralNumber = requires(T)
		{
			{ std::is_integral_v<T> };
			{ std::is_arithmetic_v<T> };
		};

		template<integralNumber T>
		std::string formatCommas(T n)
		{
			std::string s = std::to_string(n);
			std::string res = "";
			size_t len = s.length();
			size_t i = 0;
			if (len > 0 && s[0] == '-')
				res += s[i++];
			if (len > i)
				res += s[i++];
			for (; i < len; i++)
			{
				if ((len - i) % 3 == 0)
					res += ',';
				res += s[i];
			}
			return res;
		}
	}
}