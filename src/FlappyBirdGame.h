#pragma once

#include "rendering/Screen.h"
#include "Scene.h"
#include "rendering/SpriteFactory.h"

class FlappyBirdGame {
public:
    explicit FlappyBirdGame(Screen screen);

    void Act(float dt);

    void Draw();

private:
    void BuildScene();

    constexpr static const float VIEWPORT_HEIGHT = 192.f;

    Screen screen_;
    Scene scene_;
    SpriteFactory sprite_factory_;
};
