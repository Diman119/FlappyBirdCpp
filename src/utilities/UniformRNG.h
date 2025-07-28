#pragma once

#include <random>

class UniformRNG {
public:
    UniformRNG(std::random_device& rd, float low, float high);

    float Generate();

private:
    std::mt19937 engine_;
    std::uniform_real_distribution<float> distribution_;
};

