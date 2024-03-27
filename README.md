# CanvasLib

CanvasLib is a tiny c++ GLFW 2d graphics library for fast prototyping of some simulations/games/whatever. Inspired by JS canvas.


## Basic usage example
```cpp
#include <CanvasLib/CanvasLib.hpp>
 
auto main() -> int
{
    canv::Canvas canvas{ 1000, 800 };
    canvas.setUpdateFunction(
        [&canvas](double fpsScale)
        {
            canvas.setFillColor(canv::Colors::green);
            canvas.drawRectangle(100, 100, 50, 150);
        });
    canvas.start();
}
```

## Docs
Doxygen documentation is available [here](https://lolitron-0.github.io/CanvasLib/html/).
