#pragma once

#include "Surface.h"
#include <vector>

class Image : public Surface {
public:
    Image();

    Image(uint16_t width, uint16_t height);

    Image(uint16_t width, uint16_t height, const unsigned char* rle_data);

    [[nodiscard]] Image Scaled(float factor) const;

protected:
    [[nodiscard]] uint32_t* PixelData() override {
        return pixel_data_.data();
    }

    [[nodiscard]] const uint32_t* PixelData() const override {
        return pixel_data_.data();
    }

private:
    static void RLEDecode(const unsigned char* rle_data, uint32_t data_size, unsigned char* output);

    std::vector<uint32_t> pixel_data_;
};
