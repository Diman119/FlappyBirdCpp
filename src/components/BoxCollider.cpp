#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size, int collision_group) : collision_group_(collision_group), size_(size) {}

bool BoxCollider::Intersects(const BoxCollider& other) const {
    auto offset = GetGameObject()->position - other.GetGameObject()->position;
    auto combined_size = (size_ + other.size_) * 0.5f;
    return std::abs(offset.x) < combined_size.x && std::abs(offset.y) < combined_size.y;
}

void BoxCollider::OnCollision(const BoxCollider& c1, const BoxCollider& c2) {
    if (c1.collision_callback_) {
        c1.collision_callback_(c2);
    }
    if (c2.collision_callback_) {
        c2.collision_callback_(c1);
    }
}

void BoxCollider::SetCollisionCallback(std::function<void(const BoxCollider&)> callback) {
    collision_callback_ = std::move(callback);
}
