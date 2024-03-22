# CanvasLib

CanvasLib is a tiny c++ GLFW 2d graphics library for fast prototyping of some simulations/games/whatever. Inspired by JS canvas.

# Building with CMake

## Build

This project doesn't require any special command-line flags to build.

Here are the steps for building in release mode with a single-configuration
generator, like the Unix Makefiles one:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```
[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://cmake.org/cmake/help/latest/command/find_package.html

### Docs
Open index.html in docs/docs/html directory in browser. (yeah)
<!--
Please go to https://choosealicense.com/licenses/ and choose a license that
fits your needs. The recommended license for a project of this type is the
Boost Software License 1.0.
-->
