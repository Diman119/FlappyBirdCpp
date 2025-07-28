#pragma once

#include "../ecs.h"
#include "../utilities/LoopAnimator.h"
#include "../rendering/Sprite.h"

class SpriteRenderer;

class SpriteAnimator : public Component {
public:
    SpriteAnimator(std::initializer_list<Sprite> animation_frames, float animation_fps);

    void Awake() override;

    void Update(float dt) override;

private:
    std::weak_ptr<SpriteRenderer> renderer_;
    std::vector<Sprite> animation_frames_;
    LoopAnimator frame_animator_;
};
