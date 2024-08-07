#pragma once

#include <array>
#include <glm/fwd.hpp>
#include <Graphics/Textures/AtlasTexture.h>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace HotdogCraft::Graphics::Textures
{

    class TextureAtlas
    {
    public:
        TextureAtlas(std::string texName);
        ~TextureAtlas();

        void setParams(int minFilter, int magFilter);
        u32 getHandle();
        std::string getTexName() const;
        // Gets the slot size, each texture occupies a multiple of this size
        int getSlotSize() const;
        glm::ivec2 getTexSize() const;
        void bind();
        // Adds a texture to the atlas, without stitching
        void addTexture(Texture&& texture);
        std::unordered_map<std::string, AtlasTexture>& getTextures();
        void stitchAll();
        glm::mat2x2 getTexUv(std::string name) const;

    private:
        u32 handle{ 0 };
        std::string texName;
        int slotSize{ 16 };
        glm::ivec2 texSize{ 1536, 512 };
        std::unordered_map<std::string, AtlasTexture> textures{};
        std::vector<bool> slots{};

        void clear();
        std::optional<glm::ivec2> findEmptySlot(glm::ivec2 size) const;
    };
}