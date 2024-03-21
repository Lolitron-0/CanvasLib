#ifndef CANVAS_COLOR_HPP
#define CANVAS_COLOR_HPP

#include <cstdint>
#include <limits>

namespace canv
{

/**
 * @brief Utility Color class operating uint8(0..255) values
 */
class Color
{
public:
    /**
     * @brief by default creates black transparent color
     */
    Color() = default;

    /**
     * @brief creates color using 0.255 values
     */
    Color(uint8_t, uint8_t, uint8_t,
          uint8_t a = std::numeric_limits<uint8_t>::max()) noexcept;

    uint8_t R{ 0 };
    uint8_t G{ 0 };
    uint8_t B{ 0 };
    uint8_t A{ 0 };
};

} // namespace canv

#endif // CANVAS_COLOR_HPP
