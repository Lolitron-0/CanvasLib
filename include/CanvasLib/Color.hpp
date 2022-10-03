#ifndef CANVAS_COLOR_HPP
#define CANVAS_COLOR_HPP

#include "CanvasLib/CanvasLib_export.hpp"
#include <cstdint>
#include <limits>

namespace canv {

/**
 * @brief Utility Color class operating uint8(0..255) values
 */
class CANVASLIB_EXPORT Color
{
    typedef uint8_t uint8;
public:
    /**
     * @brief by default creates black transparent color
     */
    Color();
    /**
     * @brief creates color using 0.255 values
     */
    Color(uint8, uint8, uint8, uint8 a = std::numeric_limits<uint8>::max());
    Color(const Color&);

    Color& operator=(const Color& other);
    Color& operator=(Color&& other);

public:
    uint8 r,g,b,a;
};


} // namespace canvas

#endif // CANVAS_COLOR_HPP
