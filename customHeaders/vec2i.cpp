#include "vec2d.h"
#include "vec2f.h"
#include "vec2i.h"

const Vec2i Vec2i::ZERO = Vec2i(0.f, 0.f);
const Vec2i Vec2i::ONE = Vec2i(1.f, 1.f);

Vec2i::operator Vec2f() const {
    return Vec2f((float)x, (float)y);
}

Vec2i::operator Vec2d() const {
    return Vec2d((double)x, (double)y);
}
