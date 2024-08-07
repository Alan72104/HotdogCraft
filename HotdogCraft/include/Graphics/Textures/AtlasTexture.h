#pragma once

#include <fwd.h>
#include <Graphics/Textures/Texture.h>

namespace HotdogCraft::Graphics::Textures
{
    struct AtlasTexture
    {
    public:
        AtlasTexture(Texture&& tex, glm::vec2 slots);

        up<Texture> texture;
        glm::ivec2 slot{};
        // The fractional slots used
        glm::vec2 slots;
        // The fractional slots used rounded up
        glm::ivec2 slotsOccupied;
        glm::mat2x2 uv{};
        bool stitched{ false };
    };
}