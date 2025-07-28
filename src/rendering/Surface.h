#pragma once

#include <cstdint>

class Surface {
public:
    virtual ~Surface() = default;

    void Blit(Surface& target, int x, int y, bool alpha_blend = false) const {
        Blit(target, x, y, 0, width_, 0, height_, alpha_blend);
    }

    [[nodiscard]] int Width() const {
        return width_;
    }

    [[nodiscard]] int Height() const {
        return height_;
    }

    void
    Blit(Surface& target, int x, int y, int x_from, int x_to, int y_from, int y_to, bool alpha_blend = false) const;

    void VerticalFlip();

    void Clear();

protected:
    Surface(int width, int height) : width_(width), height_(height) {}

    [[nodiscard]] virtual uint32_t* PixelData() = 0;

    [[nodiscard]] virtual const uint32_t* PixelData() const = 0;

    static uint32_t AlphaBlendPixels(uint32_t p1, uint32_t p2);

    int width_;
    int height_;
};
