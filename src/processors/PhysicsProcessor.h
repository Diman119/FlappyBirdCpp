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

    void SetTimeScale(float value);

private:
    SptrVector<Rigidbody> bodies_;
    std::unordered_map<int, SptrVector<BoxCollider>> collider_groups_;
    float time_scale_ = 1.f;
};
