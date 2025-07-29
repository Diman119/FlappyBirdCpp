#pragma once

#include "Image.h"
#include "../utilities/Vector2.h"

class Sprite {
public:
    struct Coordinates {
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;
    };

    Sprite(const Image& atlas, Coordinates coordinates);

    void Blit(Surface& target, Vector2 target_position, bool alpha_blending = false) const;

    void BlitCentered(Surface& target, Vector2 target_position, bool alpha_blending = false) const;

    [[nodiscard]] uint16_t Width() const {
        return coordinates_.width;
    }

    [[nodiscard]] uint16_t Height() const {
        return coordinates_.height;
    }

private:
    Coordinates coordinates_;
    const Image* atlas_;
};
