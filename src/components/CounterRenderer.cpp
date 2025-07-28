#include "CounterRenderer.h"

CounterRenderer::CounterRenderer(std::initializer_list<Sprite> digit_sprites, int order) :
        Renderer(order),
        digit_sprites_(digit_sprites) {}

void CounterRenderer::Render(Camera& camera) {
    auto position = camera.PositionOnTarget(GetGameObject()->position);
    position.x += static_cast<float>(Width()) * 0.5f;

    for (auto d: selected_digits_) {
        const auto& sprite = digit_sprites_[d];
        auto half_width = static_cast<float>(sprite.Width()) * 0.5f;
        position.x -= half_width;
        sprite.BlitCentered(camera.Target(), position, true);
        position.x -= half_width;
    }
}

uint16_t CounterRenderer::Width() const {
    uint16_t result = 0u;
    for (auto d: selected_digits_) {
        result += digit_sprites_[d].Width();
    }
    return result;
}

void CounterRenderer::SetNumber(uint32_t number) {
    selected_digits_.clear();

    if (number == 0u) {
        selected_digits_.push_back(0u);
        return;
    }
    
    while (number > 0u) {
        auto digit = number % 10u;
        number /= 10u;
        selected_digits_.push_back(digit);
    }
}
