#pragma once

#include "../ecs.h"
#include "../utilities/UniformRNG.h"
#include <functional>

class PositionRecycler : public Component {
public:
    PositionRecycler(float threshold_x, float displacement_x);

    void SetRecycleCallback(std::function<void()> callback);

    void Update(float dt) override;

private:
    float threshold_x_;
    float displacement_x_;
    std::function<void()> recycle_callback_;
};
