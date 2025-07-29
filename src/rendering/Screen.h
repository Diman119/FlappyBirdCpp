#pragma once

#include "Surface.h"

class Screen : public Surface {
public:
    Screen(uint16_t width, uint16_t height, uint32_t* pixel_data) : Surface(width, height), pixel_data_(pixel_data) {}

protected:
    [[nodiscard]] uint32_t* PixelData() override {
        return pixel_data_;
    }

    [[nodiscard]] const uint32_t* PixelData() const override {
        return pixel_data_;
    }

private:
    uint32_t* pixel_data_;
};
