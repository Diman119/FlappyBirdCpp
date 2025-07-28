#pragma once

#include "../ecs.h"
#include "../utilities/UniformRNG.h"

class PipeHeightRandomizer : public Component {
public:
    PipeHeightRandomizer(float interval_y, UniformRNG generator_y,
                         std::weak_ptr<GameObject> second_part);

    void Awake() override;

private:
    void RandomizeY();

    std::weak_ptr<GameObject> second_part_;
    UniformRNG generator_y_;
    float interval_y_;
};
