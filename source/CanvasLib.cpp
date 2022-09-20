#include <string>

#include "CanvasLib/CanvasLib.hpp"

Canvas::Canvas()
    : m_name {"CanvasLib"}
{
}

auto Canvas::name() const -> const char*
{
  return m_name.c_str();
}
