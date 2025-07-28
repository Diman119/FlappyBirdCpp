#pragma once

class Bounds {
public:
    Bounds(float right, float left, float top, float bottom);

    [[nodiscard]] bool Intersects(const Bounds& other) const;

private:
    float right_;
    float left_;
    float top_;
    float bottom_;
};
