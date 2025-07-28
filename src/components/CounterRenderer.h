#pragma once

#include "../ecs.h"
#include "../rendering/Sprite.h"
#include "Renderer.h"

class CounterRenderer : public Renderer {
public:
    CounterRenderer(std::initializer_list<Sprite> digit_sprites, int order);

    void SetNumber(uint32_t number);

    void Render(Camera& camera) override;

private:
    [[nodiscard]] uint16_t Width() const;

    std::vector<Sprite> digit_sprites_;
    std::vector<uint8_t> selected_digits_;
};
