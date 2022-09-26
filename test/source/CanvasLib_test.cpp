#include <string>
#include <iostream>

#include "CanvasLib/CanvasLib.hpp"

auto canvas = canv::Canvas(500, 300);

auto update() -> void
{
    canvas.drawRectangle(canv::Colors::red, 20,20, 50,60);
}



auto main() -> int
{
  canvas.setUpdateFunction(update);
  canvas.start();

  return 0;
}
