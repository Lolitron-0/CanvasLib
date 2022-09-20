#include <string>

#include "CanvasLib/CanvasLib.hpp"

auto main() -> int
{
  auto const exported = exported_class {};

  return std::string("CanvasLib") == exported.name() ? 0 : 1;
}
