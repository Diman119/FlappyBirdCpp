#include "Camera.h"

Camera::Camera(Screen target, float scale) : target_(std::move(target)), scale_(scale) {}

Vector2 Camera::PositionOnTarget(Vector2 world_position) const {
    return (world_position - GetGameObject()->position) * scale_;
}
