#include "vec2d.h"
#include "vec2f.h"
#include "vec2i.h"

const Vec2f Vec2f::ZERO = Vec2f(0.f, 0.f);
const Vec2f Vec2f::ONE = Vec2f(1.f, 1.f);

Vec2f::operator Vec2d() const {
    return Vec2d((double)x, (double)y);
}

Vec2f::operator Vec2i() const {
    return Vec2i((int)x, (int)y);
}