#include "UniformRNG.h"

UniformRNG::UniformRNG(std::random_device& rd, float low, float high) :
        engine_(rd()),
        distribution_(low, high) {}

float UniformRNG::Generate() {
    return distribution_(engine_);
}
