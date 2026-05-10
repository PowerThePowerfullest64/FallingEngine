#pragma once
#include <cmath>
#include "raylib.h"

struct Vec2f;
struct Vec2d;

struct Vec2i
{
    int x;
    int y;

    // static constants
    static const Vec2i ZERO;
    static const Vec2i ONE;

    // Constructors
    constexpr Vec2i() : x(0), y(0) {}
    constexpr Vec2i(int x_, int y_) : x(x_), y(y_) {}

    // Basic operations
    constexpr Vec2i operator+(const Vec2i& rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    constexpr Vec2i operator-(const Vec2i& rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    constexpr Vec2i operator*(float scalar) const
    {
        return { (int)(x * scalar), (int)(y * scalar) };
    }

    constexpr Vec2i operator/(float scalar) const
    {
        return { (int)(x / scalar), (int)(y / scalar) };
    }

    Vec2i& operator+=(const Vec2i& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2i& operator-=(const Vec2i& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2i& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        x = (int)x;
        y = (int)y;
        return *this;
    }

    Vec2i& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        x = (int)x;
        y = (int)y;
        return *this;
    }

    bool operator==(const Vec2i &v) const
    {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vec2i &v) const
    {
        return !(*this == v);
    }

    // Length
    float length() const
    {
        return std::sqrt((float)(x * x + y * y));
    }

    float lengthSq() const
    {
        return x * x + y * y;
    }

    float distanceTo(const Vec2i& v) const
    {
        Vec2i dv = v - *this;
        return dv.length();
    }

    float distanceToSq(const Vec2i& v) const
    {
        Vec2i dv = v - *this;
        return dv.lengthSq();
    }

    Vector2 toVector2() const
    {
        return Vector2{ (float)x, (float)y };
    }

    static Vec2i fromVector2(const Vector2& v) {
        return Vec2i(v.x, v.y);
    }

    // Dot product
    static float dot(const Vec2i& a, const Vec2i& b)
    {
        return a.x * b.x + a.y * b.y;
    }
    
    operator Vec2f() const;
    operator Vec2d() const;

    operator Vector2() const {
        return {(float)x, (float)y};
    }
};
