#include "SpriteAnimator.h"
#include "SpriteRenderer.h"

SpriteAnimator::SpriteAnimator(std::initializer_list<Sprite> animation_frames, float animation_fps) :
        animation_frames_(animation_frames),
        frame_animator_(animation_fps, static_cast<float>(animation_frames_.size())) {}

void SpriteAnimator::Awake() {
    renderer_ = GetComponent<SpriteRenderer>();
}

void SpriteAnimator::Update(float dt) {
    frame_animator_.Step(dt);
    renderer_.lock()->SetSprite(animation_frames_[static_cast<size_t>(frame_animator_.Position())]);

}
