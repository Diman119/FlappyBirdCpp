#include "Rigidbody.h"

Rigidbody::Rigidbody(Vector2 initial_velocity, Vector2 gravity) : velocity(initial_velocity), gravity(gravity) {}

void Rigidbody::Step(float dt) {
    velocity += gravity * dt;
    GetGameObject()->position += velocity * dt;
}
