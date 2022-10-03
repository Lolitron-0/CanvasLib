#ifndef CANVAS_VEC2_H
#define CANVAS_VEC2_H

#include "CanvasLib/CanvasLib_export.hpp"
#include <iostream>
#include <cmath>

namespace canv {

/**
 * @brief Utility Vec2 class with x, y coordinates.
 * @tparam CoordType is type of x, y fields (float/int/double most often but can be used as tuple with number-convertible types (why?))
 */
template<typename CoordType>
class CANVASLIB_EXPORT Vec2
{
public:
    /**
     * @brief creates Vec2 with 0, 0 coordinates
     */
    Vec2()
        :x(0), y(0)
    {}
    Vec2(CoordType x, CoordType y)
        :x(x), y(y)
    {}

    Vec2(const Vec2& other) = default;

    /**
     * @brief returns distance^2 to other point
     */
    template<typename U>
    auto distToSquared(const Vec2<U>& other){
        return (x-other.x) * (x-other.x) + (y-other.y) * (y-other.y);
    }

    /**
     * @brief returns distance to other point
     */
    template<typename U>
    auto distTo(const Vec2<U>& other){
        return std::sqrt(distToSquared(other));
    }

#pragma region OPERATORS
    template<typename U>
    Vec2<CoordType>& operator+=(const Vec2<U>& other){
        x+=other.x;
        y+=other.y;
        return *this;
    }
    template<typename U>
    Vec2<CoordType>& operator-=(const Vec2<U>& other){
        x-=other.x;
        y-=other.y;
        return *this;
    }
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
#pragma endregion

public:
    CoordType x;
    CoordType y;
};

} // namespace canvas

#endif // CANVAS_VEC2_H
