#include <AssetStore.h>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <Logger.h>
#include <sstream>
#include <string>
#include <vector>

namespace HotdogCraft
{
    std::filesystem::path AssetStore::assetDir = std::filesystem::current_path() / "assets";

    AssetStore::AssetStore()
    {
        Logger::info("Asset dir is {}", assetDir.string());
    }

    std::filesystem::path AssetStore::getAssetDir()
    {
        return assetDir;
    }

    std::string AssetStore::getShader(std::string name)
    {
        auto path = assetDir / "shaders" / name;
        return getText(path);
    }

    std::vector<char> AssetStore::getTexture(std::string name)
    {
        auto path = assetDir / "textures" / name;
        return getBinary(path);
    }

    std::vector<char> AssetStore::getFont(std::string name)
    {
        auto path = assetDir / "fonts" / name;
        return getBinary(path);
    }

    std::string AssetStore::getText(std::filesystem::path path)
    {
        assert(std::filesystem::exists(path) && "File doesn't exist");
        auto fileStream = std::ifstream(path);
        std::stringstream stream;
        stream << fileStream.rdbuf();
        return stream.str();
    }

    std::vector<char> AssetStore::getBinary(std::filesystem::path path)
    {
        assert(std::filesystem::exists(path) && "File doesn't exist");
        auto fileStream = std::ifstream(path, std::ios::binary | std::ios::ate);
        std::streamsize size = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);
        std::vector<char> vec(size);
        fileStream.read(vec.data(), size);
        return vec;
    }
}