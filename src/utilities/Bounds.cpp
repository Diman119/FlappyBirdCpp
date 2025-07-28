#include "Bounds.h"

Bounds::Bounds(float right, float left, float top, float bottom) :
        right_(right),
        left_(left),
        top_(top),
        bottom_(bottom) {}

bool Bounds::Intersects(const Bounds& other) const {
    return right_ <= other.left_
           || left_ >= other.right_
           || top_ <= other.bottom_
           || bottom_ >= other.top_;
}
