#pragma once

#include <functional>
#include "../ecs.h"
#include "../utilities/Vector2.h"

struct BoxCollider : public Component {
public:
    BoxCollider(Vector2 size, int collision_group);

    [[nodiscard]] bool Intersects(const BoxCollider& other) const;

    // intersections within same group will not be processed
    [[nodiscard]] int CollisionGroup() const {
        return collision_group_;
    }

    void SetCollisionCallback(std::function<void(const BoxCollider& other)> callback);

    static void OnCollision(const BoxCollider& c1, const BoxCollider& c2);

private:
    std::function<void(const BoxCollider& other)> collision_callback_;
    int collision_group_;
    Vector2 size_;
};
