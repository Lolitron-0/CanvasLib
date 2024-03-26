#pragma once
#include <cmath>
#include <cstdint>
#include <iostream>

namespace canv
{

/**
 * @brief Utility Vec2 class with x, y coordinates.
 * @tparam CoordType is type of x, y fields
 */
template <typename T>
class Vec2
{
public:
    /**
     * @brief creates Vec2 with 0, 0 coordinates
     */
    Vec2()
        : X(0),
          Y(0)
    {
    }

    Vec2(T x, T y) // NOLINT
        : X(x),
          Y(y)
    {
    }

    /**
     * @brief returns distance^2 to other point
     */
    template <typename U>
    auto DistToSquared(const Vec2<U>& other)
    {
        return (X - other.X) * (X - other.X) + (Y - other.Y) * (Y - other.Y);
    }

    /**
     * @brief returns distance to other point
     */
    template <typename U>
    auto DistTo(const Vec2<U>& other)
    {
        return std::sqrt(DistToSquared(other));
    }

    auto AsTuple() const -> std::tuple<T, T>
    {
        return std::make_tuple(X, Y);
    }

    template <typename U>
    auto operator+=(const Vec2<U>& other) -> Vec2<T>&
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }
    template <typename U>
    auto operator-=(const Vec2<U>& other) -> Vec2<T>&
    {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

	template<typename R, typename U>
    friend auto operator*(const Vec2<R>& vec, const U& value) -> Vec2<R>;

    T X;
    T Y;
};

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int32_t>;
using Vec2ui = Vec2<uint32_t>;

template <typename T, typename U>
auto operator*(const Vec2<T>& vec, const U& value) -> Vec2<T>
{
    return { vec.X * static_cast<T>(value), vec.Y * static_cast<T>(value) };
}

} // namespace canv
