#include "SpriteFactory.h"
#include "../helpers.h"
#include <fstream>

SpriteFactory::SpriteFactory(const std::string& atlas_path, const std::string& sprite_list_path,
                             float scale_factor) :
        atlas_(LoadAtlas(atlas_path).Scaled(scale_factor)),
        coordinates_map_(LoadCoordinates(sprite_list_path)),
        scale_factor_(scale_factor) {}

Sprite SpriteFactory::Create(const std::string& name) {
    auto coords = coordinates_map_.at(name);
    coords.x = round_scale_integer(coords.x, scale_factor_);
    coords.y = round_scale_integer(coords.y, scale_factor_);
    coords.width = round_scale_integer(coords.width, scale_factor_);
    coords.height = round_scale_integer(coords.height, scale_factor_);

    return {atlas_, coords};
}

Image SpriteFactory::LoadAtlas(const std::string& path) {
    std::ifstream file{path};

    uint16_t width, height;
    uint32_t data_size;
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));
    file.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));

    std::vector<unsigned char> rle_data(data_size);
    file.read(reinterpret_cast<char*>(rle_data.data()), data_size);

    file.close();

    return {width, height, rle_data.data()};
}

std::unordered_map<std::string, Sprite::Coordinates> SpriteFactory::LoadCoordinates(const std::string& path) {
    std::unordered_map<std::string, Sprite::Coordinates> result;
    std::ifstream file{path};

    std::string sprite_name;
    Sprite::Coordinates coords{};
    while (!file.eof()) {
        file >> sprite_name >> coords.x >> coords.y >> coords.width >> coords.height;
        result.emplace(std::move(sprite_name), coords);
    }

    file.close();

    return result;
}

