#pragma once

#include "../ecs.h"
#include "Camera.h"

class Renderer : public Component {
public:
    explicit Renderer(int order) : order_(order) {}

    virtual void Render(Camera& camera) = 0;

    [[nodiscard]] int Order() const {
        return order_;
    }

private:
    int order_;
};
