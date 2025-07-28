#include "PositionRecycler.h"

PositionRecycler::PositionRecycler(float threshold_x, float displacement_x)
        : threshold_x_(threshold_x),
          displacement_x_(displacement_x) {}

void PositionRecycler::Update(float dt) {
    auto first_part = GetGameObject();
    if (first_part->position.x < threshold_x_) {
        first_part->position.x += displacement_x_;
        if (recycle_callback_) {
            recycle_callback_();
        }
    }
}

void PositionRecycler::SetRecycleCallback(std::function<void()> callback) {
    recycle_callback_ = std::move(callback);
}
