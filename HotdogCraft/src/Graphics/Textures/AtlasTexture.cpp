#include <array>
#include <glm/fwd.hpp>
#include <Graphics/Textures/AtlasTexture.h>
#include <Graphics/Textures/Texture.h>
#include <Graphics/Textures/TextureAtlas.h>
#include <memory>
#include <type_traits>

namespace HotdogCraft::Graphics::Textures
{
    AtlasTexture::AtlasTexture(Texture&& texture, glm::vec2 slots)
        : texture(std::make_unique<Texture>(std::move(texture)))
        , slots(slots)
        , slotsOccupied(glm::ceil(slots))
    {
    }
    //AtlasTexture::AtlasTexture(TextureAtlas* atlas, Texture&& texture, glm::ivec2 slot, glm::vec2 realSlots)
    //    : atlas(atlas)
    //    , texture(std::move(texture))
    //    , slot(slot)
    //    , slots(realSlots)
    //{
    //    auto aSlots = glm::vec2(atlas->getTexSize()) / (float)atlas->getSlotSize();
    //    uv =
    //    {
    //        glm::vec2(slot.x / aSlots.x,             slot.y / aSlots.y),
    //        glm::vec2((slot.x + slots.x) / aSlots.x, (slot.y + slots.y) / aSlots.y),
    //    };
    //}

    //Texture& AtlasTexture::getTexture()
    //{
    //    return texture;
    //}

    //glm::ivec2 AtlasTexture::getSlot() const
    //{
    //    return slot;
    //}

    //glm::ivec2 AtlasTexture::getOccupiedSlots() const
    //{
    //    return glm::ceil(slots);
    //}

    //glm::vec2 AtlasTexture::getRealSlots() const
    //{
    //    return slots;
    //}

    //glm::mat2x2 AtlasTexture::getUv() const
    //{
    //    return uv;
    //}
}