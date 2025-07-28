#include "TiledRenderer.h"
#include <cmath>

TiledRenderer::TiledRenderer(Sprite sprite, int order, Vector2 area_size) :
        Renderer(order),
        sprite_(sprite),
        x_copies_(std::ceil(area_size.x / static_cast<float>(sprite.Width()))),
        y_copies_(std::ceil(area_size.y / static_cast<float>(sprite.Height()))) {}

void TiledRenderer::Render(Camera& camera) {
    auto corner_position = camera.PositionOnTarget(GetGameObject()->position);
    for (int i = 0; i < x_copies_; ++i) {
        for (int j = 0; j < y_copies_; ++j) {
            sprite_.Blit(camera.Target(), corner_position + Vector2{static_cast<float>(i * sprite_.Width()),
                                                                    static_cast<float>(j * sprite_.Height())});
        }
    }
}
