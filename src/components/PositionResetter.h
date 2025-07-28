#pragma once

#include "../ecs.h"

class PositionResetter : public Component {
public:
    void Awake() override;

    void ResetPosition();

private:
    Vector2 original_position_;
};
