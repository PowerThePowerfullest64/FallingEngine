#pragma once
#include <cmath>
#include "raylib.h"
#include <cmath>
#include <algorithm>

struct Vec2f;
struct Vec2i;

struct Vec2d
{
    double x;
    double y;

    // static constants
    static const Vec2d ZERO;
    static const Vec2d ONE;

    // Constructors
    constexpr Vec2d() : x(0.0), y(0.0) {}
    constexpr Vec2d(double x_, double y_) : x(x_), y(y_) {}

    // Basic operations
    constexpr Vec2d operator+(const Vec2d& rhs) const
    {
        return { x + rhs.x, y + rhs.y };
    }

    constexpr Vec2d operator-(const Vec2d& rhs) const
    {
        return { x - rhs.x, y - rhs.y };
    }

    constexpr Vec2d operator*(double scalar) const
    {
        return { x * scalar, y * scalar };
    }

    constexpr Vec2d operator/(double scalar) const
    {
        return { x / scalar, y / scalar };
    }

    Vec2d& operator+=(const Vec2d& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2d& operator-=(const Vec2d& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2d& operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2d& operator/=(double scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vec2d &v) const
    {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vec2d &v) const
    {
        return !(*this == v);
    }

    // Length
    double length() const
    {
        return std::sqrt(x * x + y * y);
    }

    double lengthSq() const
    {
        return x * x + y * y;
    }

    double distanceTo(const Vec2d& v) const
    {
        Vec2d dv = v - *this;
        return dv.length();
    }

    double distanceToSq(const Vec2d& v) const
    {
        Vec2d dv = v - *this;
        return dv.lengthSq();
    }

    // Normalization
    Vec2d normalized() const
    {
        double len = length();
        if (len == 0.0) return {0.0, 0.0};
        return { x / len, y / len };
    }

    void normalize()
    {
        double len = length();
        if (len == 0.0) return;
        x /= len;
        y /= len;
    }

    // Conversion to Raylib Vector2
    Vector2 toVector2() const
    {
        return Vector2{ (float)x, (float)y };
    }

    double toAngle() const
    {
        return atan2(y, x);
    }

    static Vec2d fromAngle(double angle)
    {
        Vec2d v;
        v.x = cos(angle);
        v.y = sin(angle);

        return v;
    }

    double toAngleD() const
    {
        return atan2(y, x) * 180.f / PI;;
    }


    static Vec2d fromVector2(const Vector2& v) {
        return Vec2d(v.x, v.y);
    }

    // Dot product
    static double dot(const Vec2d& a, const Vec2d& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    operator Vec2f() const;
    operator Vec2i() const;

    static Vec2d lerp(const Vec2f& a, const Vec2f& b, double t);
    static Vec2f fromAngleD(double angle);

    operator Vector2() const {
        return {(float)x, (float)y};
    }
};
