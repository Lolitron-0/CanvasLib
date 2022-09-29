#ifndef CANVAS_VEC2_H
#define CANVAS_VEC2_H

#include "CanvasLib/CanvasLib_export.hpp"
#include <iostream>

namespace canv {

template<typename CoordType>
class CANVASLIB_EXPORT Vec2
{
public:
    Vec2()
        :x(0), y(0)
    {}
    Vec2(CoordType x, CoordType y)
        :x(x), y(y)
    {}

    Vec2(const Vec2& other) = default;

    Vec2<CoordType>& operator=(const Vec2<CoordType>& other){
        Vec2 tmp(other);
        std::swap(tmp.x, this->x);
        std::swap(tmp.y, this->y);
        return *this;
    }
    Vec2<CoordType>& operator=(const Vec2<CoordType>&& other){
        std::swap(other.x, this->x);
        std::swap(other.y, this->y);
        return *this;
    }

public:
    CoordType x;
    CoordType y;
};

} // namespace canvas

#endif // CANVAS_VEC2_H
