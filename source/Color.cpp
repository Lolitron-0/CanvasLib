#include "CanvasLib/Color.hpp"
#include <iostream>

namespace canv
{

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept // NOLINT
    : R(r),
      G(g),
      B(b),
      A(a)
{
}

} // namespace canv
