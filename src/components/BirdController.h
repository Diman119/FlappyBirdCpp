#pragma once

#include "../ecs.h"
#include "../utilities/Vector2.h"
#include "../Engine.h"

class Rigidbody;

class BirdController : public Component {
public:
    BirdController(int jump_button_code,
                   float jump_y_speed,
                   float max_y_speed);

    void Awake() override;

    void Update(float dt) override;

private:
    std::weak_ptr<Rigidbody> rigidbody_;
    int jump_button_code_;
    bool jump_was_pressed_ = false;
    float jump_y_speed_;
    float max_y_speed_;
};
