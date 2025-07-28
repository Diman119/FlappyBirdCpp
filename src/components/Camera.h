#pragma once

#include "../ecs.h"
#include "../utilities/Vector2.h"
#include "../rendering/Screen.h"

class Camera : public Component {
public:
    Camera(Screen target, float scale);

    Screen& Target() {
        return target_;
    }

    [[nodiscard]] Vector2 PositionOnTarget(Vector2 world_position) const;

private:
    Screen target_;
    float scale_;
};
