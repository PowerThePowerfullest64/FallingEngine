#include "vec2d.h"
#include "vec2f.h"
#include "vec2i.h"

const Vec2d Vec2d::ZERO = Vec2d(0.f, 0.f);
const Vec2d Vec2d::ONE = Vec2d(1.f, 1.f);

Vec2d::operator Vec2f() const {
    return Vec2f((float)x, (float)y);
}

Vec2d::operator Vec2i() const {
    return Vec2i((int)x, (int)y);
}

Vec2d Vec2d::lerp(const Vec2f& a, const Vec2f& b, double t) {
    t = std::clamp(t, 0.0, 1.0);
    return {
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y)
    };
}

Vec2f Vec2d::fromAngleD(double angle) {
    angle *= 180.0 / PI;
    Vec2f v;
    v.x = cos(angle);
    v.y = sin(angle);
    return v;
}
