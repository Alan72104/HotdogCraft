#include <algorithm>
#include <array>
#include <fwd.h>
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <Graphics/GlHelpers.h>
#include <Graphics/Textures/AtlasTexture.h>
#include <Graphics/Textures/Texture.h>
#include <Graphics/Textures/TextureAtlas.h>
#include <Logger.h>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <type_traits>
#include <vector>

namespace HotdogCraft::Graphics::Textures
{
    TextureAtlas::TextureAtlas(std::string texName)
        : texName(texName)
    {
    }

    TextureAtlas::~TextureAtlas()
    {
        if (handle)
            glDeleteTextures(1, &handle);
    }

    void TextureAtlas::setParams(int minFilter, int magFilter)
    {
        bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        GlHelpers::checkError();
    }

    u32 TextureAtlas::getHandle()
    {
        if (!handle)
        {
            glGenTextures(1, &handle);
            bind();
            glObjectLabel(GL_TEXTURE, handle, -1, std::format("Texture {}", texName).c_str());
            setParams(GL_NEAREST, GL_NEAREST);
            clear();
            Logger::info("Texture atlas {} loaded", texName);
        }
        return handle;
    }

    std::string TextureAtlas::getTexName() const
    {
        return texName;
    }

    int TextureAtlas::getSlotSize() const
    {
        return slotSize;
    }

    glm::ivec2 TextureAtlas::getTexSize() const
    {
        return texSize;
    }

    void TextureAtlas::bind()
    {
        glBindTexture(GL_TEXTURE_2D, getHandle());
    }

    void TextureAtlas::addTexture(Texture&& tex)
    {
        if (textures.contains(tex.getName()))
            return;
        glm::vec2 slots = tex.getSize() / slotSize;
        if (tex.getSize().x > texSize.x || tex.getSize().y > texSize.y)
        {
            Logger::error("Texture {} size is too large {}",
                tex.getName(), tex.getSize());
            return;
        }
        AtlasTexture at(std::move(tex), slots);
        textures.emplace(at.texture->getName(), std::move(at));
    }

    std::unordered_map<std::string, AtlasTexture>& TextureAtlas::getTextures()
    {
        return textures;
    }

    void TextureAtlas::stitchAll()
    {
        bind();
        auto sorted = textures
            | std::views::transform([](auto& pair)
                { return std::ref(pair.second); })
            | std::ranges::to<std::vector>();
        std::ranges::sort(sorted, [](auto& a, auto& b)
            {
                auto sa = a.get().texture->getSize();
                auto sb = b.get().texture->getSize();
                if (sa.x == sb.x)
                    return sa.y > sb.y;
                return sa.x > sb.x;
            });
        auto aSlots = glm::vec2(texSize) / (float)slotSize;
        for (auto& _at : sorted)
        {
            auto& at = _at.get();
            auto emptySlot = findEmptySlot(at.slotsOccupied);
            if (!emptySlot)
            {
                Logger::error("Can't find an empty slot of size {} for texture {}",
                    at.slotsOccupied, at.texture->getName());
                return;
            }
            for (int j : iota(emptySlot->y, emptySlot->y + at.slotsOccupied.y))
                for (int i : iota(emptySlot->x, emptySlot->x + at.slotsOccupied.x))
                {
                    auto idx = j * (texSize.x / slotSize) + i;
                    this->slots[idx] = true;
                }
            at.stitched = true;
            at.slot = *emptySlot;
            at.uv =
            {
                glm::vec2(at.slot.x / aSlots.x,                at.slot.y / aSlots.y),
                glm::vec2((at.slot.x + at.slots.x) / aSlots.x, (at.slot.y + at.slots.y) / aSlots.y),
            };
            glTexSubImage2D(GL_TEXTURE_2D, 0,
                at.slot.x * slotSize,
                at.slot.y * slotSize,
                at.texture->getSize().x,
                at.texture->getSize().y,
                at.texture->getChannels() == 3 ? GL_RGB : GL_RGBA,
                GL_UNSIGNED_BYTE,
                at.texture->getData().data());
            GlHelpers::checkError();
        }
    }

    glm::mat2x2 TextureAtlas::getTexUv(std::string name) const
    {
        if (!textures.contains(name))
        {
            Logger::warning("Tried to get nonexistent texture {} in atlas", name);
            return {};
        }
        const AtlasTexture& at = textures.at(name);
        if (at.stitched == false)
        {
            Logger::warning("Texture {} is not stitched yet", name);
            return {};
        }
        return at.uv;
    }

    void TextureAtlas::clear()
    {
        Logger::myAssert(handle != 0, "Atlas handle should be generated");

        bind();
        std::vector<char> emptyData(texSize.x * texSize.y * 4);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texSize.x, texSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, emptyData.data());

        slots.clear();
        slots.resize(((size_t)texSize.x / slotSize) * ((size_t)texSize.y / slotSize));

        for (auto& [_, tex] : textures)
        {
            tex.stitched = false;
        }
    }

    std::optional<glm::ivec2> TextureAtlas::findEmptySlot(glm::ivec2 size) const
    {
        for (int j : iota(0, texSize.y / slotSize - size.y + 1))
            for (int i : iota(0, texSize.x / slotSize - size.x + 1))
            {
                for (int jj : iota(j, j + size.y))
                    for (int ii : iota(i, i + size.x))
                    {
                        auto idx = jj * (texSize.x / slotSize) + ii;
                        if (slots[idx] == true)
                            goto next;
                    }
                return { {i,j} };
            next:;
            }
        return {};
    }
}