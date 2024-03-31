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
## Building with CMake
### Dependencies
The only dependency is `glfw` library. You can install it via your favorite package manager. For exmple:
 * `sudo apt-get install libglfw3 libglfw3-dev` 

Or use Nix flakes. 


### Adding to your project:
```cmake
include(FetchContent)
FetchContent_Declare(CanvasLib
    GIT_REPOSITORY "https://github.com/Lolitron-0/CanvasLib"
    GIT_TAG "origin/master"
)
FetchContent_MakeAvailable(CanvasLib)

target_link_libraries(foobarbaz PUBLIC CanvasLib)
```

## Docs
Doxygen documentation is available [here](https://lolitron-0.github.io/CanvasLib/html/).
