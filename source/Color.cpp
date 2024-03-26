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

Color::Color(const glm::vec4& glmColor)
    : Color(glmColor.r * 255, glmColor.g * 255, glmColor.b * 255,
            glmColor.a * 255)
{
}

Color::operator glm::vec4() const
{
    return { static_cast<float>(R) / 255.F, static_cast<float>(G) / 255.F,
             static_cast<float>(B) / 255.F, static_cast<float>(A) / 255.F };
}
} // namespace canv
