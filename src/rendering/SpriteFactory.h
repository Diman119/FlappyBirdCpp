#pragma once

#include "Sprite.h"
#include <string>
#include <unordered_map>

class SpriteFactory {
public:
    SpriteFactory(const std::string& atlas_path, const std::string& sprite_list_path, float scale_factor);

    [[nodiscard]] float Scale() const {
        return scale_factor_;
    }

    Sprite Create(const std::string& name);

private:
    static Image LoadAtlas(const std::string& path);

    static std::unordered_map<std::string, Sprite::Coordinates> LoadCoordinates(const std::string& path);

    Image atlas_;
    std::unordered_map<std::string, Sprite::Coordinates> coordinates_map_;
    float scale_factor_ = 1.f;
};
