#pragma once

#include <fwd.h>
#include <stb_image.h>
#include <string>
#include <vector>

namespace HotdogCraft::Graphics::Textures
{
    class Texture
    {
    public:
        Texture(std::string texName);
        Texture(const Texture&) = delete;
        Texture(Texture&&) = default;
        ~Texture();
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) = default;

        void setParams(int minFilter, int magFilter);
        std::string getName() const;
        glm::ivec2 getSize() const;
        int getChannels() const;
        const std::vector<u8>& getData() const;
        u32 getHandle();
        void bind();

        static std::vector<u8> copyAndFlip(std::vector<u8>& data, glm::ivec2 size, int channels);

    private:
        std::vector<u8> data{};
        u32 handle{ 0 };
        std::string texName;
        glm::ivec2 size;
        int channels;
    };
}