#include "../helpers.h"
#include "SpriteFactory.h"

SpriteFactory::SpriteFactory(const std::unordered_map<std::string, SpriteCoordinates>& coordinates, const Image& atlas,
                             float scale_factor)
        : coordinates_map_(coordinates), atlas_(atlas.Scaled(scale_factor)), scale_factor_(scale_factor) {}

Sprite SpriteFactory::Create(const std::string& name) {
    auto coords = coordinates_map_.at(name);
    coords.x = round_scale_integer(coords.x, scale_factor_);
    coords.y = round_scale_integer(coords.y, scale_factor_);
    coords.width = round_scale_integer(coords.width, scale_factor_);
    coords.height = round_scale_integer(coords.height, scale_factor_);

    return {atlas_, coords};
}
