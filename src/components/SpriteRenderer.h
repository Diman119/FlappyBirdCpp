#pragma once

#include "../rendering/Sprite.h"
#include "Renderer.h"

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer(Sprite sprite, int order);

    void Render(Camera& camera) override;

    void SetSprite(Sprite sprite);

private:
    Sprite sprite_;
};
