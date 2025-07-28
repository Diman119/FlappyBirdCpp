#include "PhysicsProcessor.h"
#include "../Scene.h"
#include "../components/Rigidbody.h"
#include "../components/BoxCollider.h"

void PhysicsProcessor::Initialize(const Scene& scene) {
    scene.GetComponents<Rigidbody>(bodies_);

    SptrVector<BoxCollider> all_colliders;
    scene.GetComponents<BoxCollider>(all_colliders);
    for (const auto& collider: all_colliders) {
        auto group_index = collider->CollisionGroup();
        auto it = collider_groups_.find(group_index);
        if (it == collider_groups_.end()) {
            it = collider_groups_.emplace(group_index, SptrVector<BoxCollider>{}).first;
        }
        it->second.push_back(collider);
    }
}

void PhysicsProcessor::Step(float dt) {
    for (const auto& body: bodies_) {
        body->Step(dt);
    }

    for (const auto& p1: collider_groups_) {
        for (const auto& p2: collider_groups_) {
            if (p1.first >= p2.first) {
                continue;
            }
            for (const auto& col1: p1.second) {
                for (const auto& col2: p2.second) {
                    if (col1->Intersects(*col2)) {
                        BoxCollider::OnCollision(*col1, *col2);
                    }
                }
            }
        }
    }
}

void PhysicsProcessor::Clear() {
    bodies_.clear();
    collider_groups_.clear();
}
