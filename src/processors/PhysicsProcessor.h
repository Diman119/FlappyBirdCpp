#pragma once

#include "../ecs.h"
#include <unordered_map>

class Scene;

class Rigidbody;

class BoxCollider;

class PhysicsProcessor {
public:
    void Initialize(const Scene& scene);

    void Clear();

    void Step(float dt);

private:
    SptrVector<Rigidbody> bodies_;
    std::unordered_map<int, SptrVector<BoxCollider>> collider_groups_;
};
