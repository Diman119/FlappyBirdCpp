#pragma once

#include "../ecs.h"
#include "../utilities/Vector2.h"

class Rigidbody : public Component {
public:
    Rigidbody(Vector2 initial_velocity, Vector2 gravity);

    void Step(float dt);

    Vector2 velocity;
    Vector2 gravity;
};
