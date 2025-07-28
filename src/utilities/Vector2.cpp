#include "Vector2.h"

Vector2::Vector2() : Vector2(0.f, 0.f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
    auto copy = lhs;
    copy += rhs;
    return copy;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
    auto copy = lhs;
    copy -= rhs;
    return copy;
}

Vector2 operator*(const Vector2& vec, float scalar) {
    auto copy = vec;
    copy *= scalar;
    return copy;
}

Vector2 operator*(float scalar, const Vector2& vec) {
    auto copy = vec;
    copy *= scalar;
    return copy;
}

Vector2 operator/(const Vector2& vec, float scalar) {
    auto copy = vec;
    copy /= scalar;
    return copy;
}

bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

const Vector2 Vector2::zero{0.f, 0.f};
