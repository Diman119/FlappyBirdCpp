#include <cmath>
#include "Sprite.h"

Sprite::Sprite(const Image& atlas, Coordinates coordinates) : coordinates_(coordinates), atlas_(&atlas) {}

void Sprite::Blit(Surface& target, Vector2 target_position, bool alpha_blending) const {
    atlas_->Blit(target, static_cast<int>(std::round(target_position.x)),
                 static_cast<int>(std::round(target_position.y)), coordinates_.x, coordinates_.x + coordinates_.width,
                 coordinates_.y,
                 coordinates_.y + coordinates_.height, alpha_blending);
}

void Sprite::BlitCentered(Surface& target, Vector2 target_position, bool alpha_blending) const {
    Blit(target,
         target_position -
         Vector2{static_cast<float>(coordinates_.width), static_cast<float>(coordinates_.height)} * 0.5f,
         alpha_blending);
}

