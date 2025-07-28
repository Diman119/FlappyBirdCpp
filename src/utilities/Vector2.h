#pragma once

struct Vector2 {
    Vector2();

    Vector2(float x, float y);

    Vector2& operator+=(const Vector2& other);

    Vector2& operator-=(const Vector2& other);

    Vector2& operator*=(float scalar);

    Vector2& operator/=(float scalar);

    float x;
    float y;

    static const Vector2 zero;
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

Vector2 operator*(const Vector2& vec, float scalar);

Vector2 operator*(float scalar, const Vector2& vec);

Vector2 operator/(const Vector2& vec, float scalar);

bool operator==(const Vector2& lhs, const Vector2& rhs);
