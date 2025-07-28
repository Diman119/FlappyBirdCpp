#pragma once

#include "../rendering/Sprite.h"
#include "Renderer.h"

class TiledRenderer : public Renderer {
public:
    TiledRenderer(Sprite sprite, int order, Vector2 area_size);

    void Render(Camera& camera) override;

private:
    Sprite sprite_;
    int x_copies_;
    int y_copies_;
};
