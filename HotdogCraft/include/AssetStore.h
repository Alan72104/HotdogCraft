#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

namespace HotdogCraft
{
	class AssetStore
	{
	public:
		AssetStore();

		std::filesystem::path getAssetDir();
		std::string getShader(std::string name);
		std::vector<char> getTexture(std::string name);
		std::vector<char> getFont(std::string name);

	private:
		static std::filesystem::path assetDir;

		std::string getText(std::filesystem::path path);
		std::vector<char> getBinary(std::filesystem::path path);
	};
}