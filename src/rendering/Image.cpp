#include "Image.h"
#include "../helpers.h"
#include <cstring>

Image::Image() : Image(0, 0) {}

Image::Image(uint16_t width, uint16_t height) : Surface(width, height), pixel_data_(width * height) {}

Image::Image(uint16_t width, uint16_t height, const unsigned char* rle_data) :
        Image(width, height) {
    RLEDecode(rle_data, pixel_data_.size(), reinterpret_cast<unsigned char*>(pixel_data_.data()));
}

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

void Image::RLEDecode(const unsigned char* rle_data, uint32_t data_size, unsigned char* output) {
    static const auto bits_per_pixel = 4;
    const auto* end = output + (data_size) * bits_per_pixel;
    while (output < end) {
        int byte = *(rle_data++);
        if (byte & 128) {
            byte = byte - 128;
            do {
                memcpy(output, rle_data, bits_per_pixel);
                output += bits_per_pixel;
            } while (--byte);
            rle_data += bits_per_pixel;
        } else {
            byte *= bits_per_pixel;
            memcpy(output, rle_data, byte);
            output += byte;
            rle_data += byte;
        }
    }
}
