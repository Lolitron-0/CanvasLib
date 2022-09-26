#pragma once

#include <string>
#include <functional>
#include <memory>

#include "CanvasLib/CanvasLib_export.hpp"
#include "CanvasLib/Color.hpp"
#include "CanvasLib/Vec2.hpp"
#include <GLFW/glfw3.h>

namespace CANVASLIB_EXPORT canv {

    /**
     * @brief The main class representing the canvas.
     * To use it you only need to:
     * - create Canvas object
     * - specify update function (setUpdateFunction() method)
     * - call start() method
     */
    class CANVASLIB_EXPORT Canvas
    {
    public:
      /**
       * @brief Initializes the name field to the name of the project
       */
      Canvas(int width, int height);

      /**
       * @brief starts the main window cycle IN MAIN THREAD
       */
      void start();
      /**
       * @brief sets update function that will be called every frame
       * @param upd function with void(void) signature (or lambda)
       */
      void setUpdateFunction(std::function<void(void)> upd);

      /**
       * @brief draws a rectangle with specified coordinates and size
       */
      void drawRectangle(Color color, float x, float y, float w, float h);

      ~Canvas();

    private:
      float xToGl(float x);
      float yToGl(float y);


    private:
      CANVASLIB_SUPPRESS_C4251
      std::shared_ptr<GLFWwindow> mpWindowHandle;
      std::function<void(void)> mUpdateFunction;
      Vec2<int> mSize;
    };

}
