#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Sprite sprite, int order) : Renderer(order), sprite_(sprite) {}

void SpriteRenderer::Render(Camera& camera) {
    sprite_.BlitCentered(camera.Target(), camera.PositionOnTarget(GetGameObject()->position), true);
}

void SpriteRenderer::SetSprite(Sprite sprite) {
    sprite_ = sprite;
}
