#pragma once
#include <cmath>
#include "raylib.h"
#include <cmath>
#include <algorithm>

struct Vec2d;
struct Vec2i;

struct Vec2f
{
    float x;
    float y;

    // static constants
    static const Vec2f ZERO;
    static const Vec2f ONE;

    // constructors
    constexpr Vec2f() : x(0.0f), y(0.0f) {}
    constexpr Vec2f(float x_, float y_) : x(x_), y(y_) {}

    // early declaration
    Vec2i toVec2i() const;
    Vec2d toVec2d() const;

    // Basic operations
    constexpr Vec2f operator+(const Vec2f& rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    constexpr Vec2f operator-(const Vec2f& rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    constexpr Vec2f operator*(float scalar) const
    {
        return { x * scalar, y * scalar };
    }

    constexpr Vec2f operator/(float scalar) const
    {
        return { x / scalar, y / scalar };
    }

    Vec2f& operator+=(const Vec2f& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2f& operator-=(const Vec2f& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2f& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2f& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vec2f &v) const
    {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vec2f &v) const
    {
        return !(*this == v);
    }

    // Length
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    float lengthSq() const
    {
        return x * x + y * y;
    }

    float distanceTo(const Vec2f& v) const
    {
        Vec2f dv = v - *this;
        return dv.length();
    }

    float distanceToSq(const Vec2f& v) const
    {
        Vec2f dv = v - *this;
        return dv.lengthSq();
    }

    // Normalization
    Vec2f normalized() const
    {
        float len = length();
        if (len == 0.0f) return {0.0f, 0.0f};
        return { x / len, y / len };
    }

    void normalize()
    {
        float len = length();
        if (len == 0.0f) return;
        x /= len;
        y /= len;
    }

    // Conversion to Raylib Vector2
    Vector2 toVector2() const
    {
        return Vector2{ x, y };
    }

    float toAngleR() const
    {
        return atan2(y, x);
    }

    static Vec2f fromAngleR(float angle)
    {
        Vec2f v;
        v.x = cos(angle);
        v.y = sin(angle);

        return v;
    }

    float toAngleD() const
    {
        return atan2(y, x) * 180.f / PI;;
    }

    static Vec2f fromAngleD(float angle)
    {
        angle *= DEG2RAD;
        Vec2f v;
        v.x = cos(angle);
        v.y = sin(angle);

        return v;
    }

    static Vec2f fromVector2(const Vector2& v) {
        return Vec2f(v.x, v.y);
    }

    // Dot product
    static float dot(const Vec2f& a, const Vec2f& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    static Vec2f lerp(const Vec2f& a, const Vec2f& b, float t) {
        t = std::clamp(t, 0.f, 1.f);
        return {
            a.x + t * (b.x - a.x),
            a.y + t * (b.y - a.y)
        };
    }

    operator Vec2d() const;
    operator Vec2i() const;

    operator Vector2() const {
        return {(float)x, (float)y};
    }
};
