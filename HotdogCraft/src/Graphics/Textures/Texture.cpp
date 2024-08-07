#include <cassert>
#include <cstring>
#include <format>
#include <fwd.h>
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <Graphics/GlHelpers.h>
#include <Graphics/Textures/Texture.h>
#include <HotdogCraft.h>
#include <Logger.h>
#include <ranges>
#include <stb_image.h>
#include <string>
#include <vector>

namespace HotdogCraft::Graphics::Textures
{
    Texture::Texture(std::string texName)
        : texName(texName)
    {
        auto path = HotdogCraft::ins().getAssetStore().getAssetDir() / "textures" / texName;
        int originalChannels = 0;
        int desiredChannels = 4;
        cup<u8> data = cup<u8>(stbi_load(path.string().c_str(), &size.x, &size.y, &originalChannels, desiredChannels));
        if (originalChannels != desiredChannels && !(originalChannels == 3 || originalChannels == 4))
        {
            Logger::verbose("Texture {} channel count was converted from {} to {}", texName, originalChannels, desiredChannels);
        }
        channels = desiredChannels;
        this->data.resize((size_t)size.x * size.y * channels);
        memcpy(this->data.data(), data.get(), this->data.size());
    }

    Texture::~Texture()
    {
        if (handle)
            glDeleteTextures(1, &handle);
    }

    void Texture::setParams(int minFilter, int magFilter)
    {
        bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        GlHelpers::checkError();
    }

    std::string Texture::getName() const
    {
        return texName;
    }

    glm::ivec2 Texture::getSize() const
    {
        return size;
    }

    int Texture::getChannels() const
    {
        return channels;
    }

    const std::vector<u8>& Texture::getData() const
    {
        return data;
    }

    std::vector<u8> Texture::copyAndFlip(std::vector<u8>& data, glm::ivec2 size, int channels)
    {
        std::vector<u8> copy = data;
        int rowBytes = size.x * channels;
        std::vector<u8> tempRow(rowBytes);
        for (int y : iota(0, size.y / 2))
        {
            memcpy(tempRow.data(), &copy[y * rowBytes], rowBytes);
            memcpy(&copy[y * rowBytes], &copy[(size.y - 1 - y) * rowBytes], rowBytes);
            memcpy(&copy[(size.y - 1 - y) * rowBytes], tempRow.data(), rowBytes);
        }
        return copy;
    }

    u32 Texture::getHandle()
    {
        if (!handle)
        {
            glGenTextures(1, &handle);
            bind();
            glObjectLabel(GL_TEXTURE, handle, -1, std::format("Texture {}", texName).c_str());
            setParams(GL_NEAREST, GL_NEAREST);

            if (channels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
            else if (channels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
            else
                assert(false && "Illegal texture channel count");
            Logger::info("Texture {} loaded", texName);
        }
        return handle;
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, getHandle());
    }
}