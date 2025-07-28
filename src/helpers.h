#pragma once

#include <cmath>

template<typename T>
T round_scale_integer(T integer, float factor) {
    return static_cast<T>(std::round(static_cast<float>(integer) * factor));
}

template<typename T>
T floor_scale_integer(T integer, float factor) {
    return static_cast<T>(std::floor(static_cast<float>(integer) * factor));
}