#pragma once

#include <string>

#include "CanvasLib/CanvasLib_export.hpp"
#include <GLFW/glfw3.h>


/**
 * @brief Reports the name of the library
 */
class CANVASLIB_EXPORT Canvas
{
public:
  /**
   * @brief Initializes the name field to the name of the project
   */
  Canvas();

  ~Canvas();

private:
  CANVASLIB_SUPPRESS_C4251
  GLFWwindow* mpWindowHandle;
};
