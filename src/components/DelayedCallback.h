#pragma once

#include "../ecs.h"
#include <functional>

class DelayedCallback : public Component {
public:
    explicit DelayedCallback(float delay_seconds);

    void SetCallback(std::function<void()> callback);

    void Reset(float new_delay);

    void Update(float dt) override;

private:
    std::function<void()> callback_;
    float time_left_;
};
