#pragma once

#include "Image.h"
#include "../textures/SpriteList.h"
#include "../utilities/Vector2.h"

class Sprite {
public:
    Sprite(const Image& atlas, SpriteCoordinates coordinates);

    void Blit(Surface& target, Vector2 target_position, bool alpha_blending = false) const;

    void BlitCentered(Surface& target, Vector2 target_position, bool alpha_blending = false) const;

    [[nodiscard]] uint16_t Width() const {
        return coordinates_.width;
    }

    [[nodiscard]] uint16_t Height() const {
        return coordinates_.height;
    }

private:
    SpriteCoordinates coordinates_;
    const Image* atlas_;
};
