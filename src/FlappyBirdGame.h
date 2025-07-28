#pragma once

#include <vector>
#include <memory>
#include <random>
#include "rendering/Screen.h"
#include "rendering/Image.h"
#include "textures/atlas.c"
#include "rendering/SpriteFactory.h"
#include "helpers.h"
#include "Scene.h"
#include "components/SpriteRenderer.h"
#include "components/TiledRenderer.h"
#include "components/Rigidbody.h"
#include "components/BirdController.h"
#include "components/SpriteAnimator.h"
#include "components/PositionRecycler.h"
#include "components/PipeHeightRandomizer.h"
#include "components/BoxCollider.h"

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
