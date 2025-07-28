#pragma once

#include "../textures/SpriteList.h"
#include "Sprite.h"

class SpriteFactory {
public:
    SpriteFactory(const std::unordered_map<std::string, SpriteCoordinates>& coordinates, const Image& atlas,
                  float scale_factor);

    [[nodiscard]] float Scale() const {
        return scale_factor_;
    }

    Sprite Create(const std::string& name);

private:
    const std::unordered_map<std::string, SpriteCoordinates>& coordinates_map_;
    Image atlas_;
    float scale_factor_ = 1.f;
};
