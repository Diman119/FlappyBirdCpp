#include "Surface.h"
#include <algorithm>
#include <cstring>

uint32_t Surface::AlphaBlendPixels(uint32_t p1, uint32_t p2) {
    static const uint32_t AMASK = 0xFF000000;
    static const uint32_t RBMASK = 0x00FF00FF;
    static const uint32_t GMASK = 0x0000FF00;
    static const uint32_t AGMASK = AMASK | GMASK;
    static const uint32_t ONEALPHA = 0x01000000;
    uint32_t a = (p2 & AMASK) >> 24;
    uint32_t na = 255 - a;
    uint32_t rb = ((na * (p1 & RBMASK)) + (a * (p2 & RBMASK))) >> 8;
    uint32_t ag = (na * ((p1 & AGMASK) >> 8)) + (a * (ONEALPHA | ((p2 & GMASK) >> 8)));
    return ((rb & RBMASK) | (ag & AGMASK));
}

void Surface::Blit(Surface& target, int target_x, int target_y, int x_from, int x_to, int y_from, int y_to,
                   bool alpha_blend) const {
    if (target_x < 0) {
        x_from -= target_x;
        target_x = 0;
    }
    if (target_y < 0) {
        y_from -= target_y;
        target_y = 0;
    }

    auto x_offset = target_x - x_from;
    auto y_offset = target_y - y_from;
    x_to = std::min(x_to, target.width_ - x_offset);
    y_to = std::min(y_to, target.height_ - y_offset);

    if (x_to <= x_from || y_to <= y_from) {
        return;
    }

    const auto* this_data = PixelData();
    auto* target_data = target.PixelData();

    if (alpha_blend) {
        for (int y = y_from; y < y_to; ++y) {
            for (int x = x_from; x < x_to; ++x) {
                auto* output = target_data + (y_offset + y) * target.width_ + x_offset + x;
                *output = AlphaBlendPixels(*output, this_data[y * width_ + x]);
            }
        }
    } else {
        const auto fragment_height = y_to - y_from;
        const auto fragment_width_bytes = (x_to - x_from) * sizeof(uint32_t);

        for (int y = 0; y < fragment_height; ++y) {
            memcpy(target_data + (y + target_y) * target.width_ + target_x, this_data + (y + y_from) * width_ + x_from,
                   fragment_width_bytes);
        }
    }
}

void Surface::VerticalFlip() {
    auto* data = PixelData();
    for (int y = 0; y < height_ / 2; ++y) {
        for (int x = 0; x < width_; ++x) {
            std::swap(data[y * width_ + x], data[(height_ - 1 - y) * width_ + x]);
        }
    }
}

void Surface::Clear() {
    memset(PixelData(), 0, width_ * height_ * sizeof(uint32_t));
}
