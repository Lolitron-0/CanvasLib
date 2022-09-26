#ifndef CANVAS_COLOR_HPP
#define CANVAS_COLOR_HPP

#include "CanvasLib/CanvasLib_export.hpp"
#include <cstdint>
#include <limits>
namespace canv {

class CANVASLIB_EXPORT Color
{
    typedef uint8_t uint8;
public:
    Color();
    Color(uint8, uint8, uint8, uint8 a = std::numeric_limits<uint8>::max());
    Color(const Color&) = default;

    Color& operator=(const Color& other);
    Color& operator=(Color&& other);

public:
    uint8 r,g,b,a;
};


namespace Colors {
    const Color white(255,255,255);
    const Color black(0,0,0);
    const Color grey(127, 127, 127);
    const Color red(255,0,0);
    const Color green(0,255,0);
    const Color blue(0,0,255);
    const Color lightBlue(127,178,255);
}

} // namespace canvas

#endif // CANVAS_COLOR_HPP
