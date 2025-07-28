#pragma once

#include "../ecs.h"
#include <functional>

class KeyTrigger : public Component {
public:
    explicit KeyTrigger(int key_code);

    void SetCallback(std::function<void()> callback);

    void Update(float dt) override;

private:
    std::function<void()> callback_;
    int key_code_;
};
