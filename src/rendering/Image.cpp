#include "Image.h"
#include "../helpers.h"

Image Image::Scaled(float factor) const {
    auto scaled_width = floor_scale_integer(width_, factor);
    auto scaled_height = floor_scale_integer(height_, factor);
    auto rfactor = 1.f / factor;
    auto result = Image(scaled_width, scaled_height);

    for (int y = 0; y < scaled_height; ++y) {
        int orig_y = std::floor((static_cast<float>(y) + 0.5f) * rfactor);
        for (int x = 0; x < scaled_width; ++x) {
            int orig_x = std::floor((static_cast<float>(x) + 0.5f) * rfactor);
            result.pixel_data_[y * scaled_width + x] = pixel_data_[orig_y * width_ + orig_x];
        }
    }

    return result;
}
