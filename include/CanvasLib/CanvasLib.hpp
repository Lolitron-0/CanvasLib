#pragma once

#include <string>
#include <functional>
#include <memory>

#include "CanvasLib/CanvasLib_export.hpp"
#include "CanvasLib/Color.hpp"
#include "CanvasLib/Colors.hpp"
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
    enum class CANVASLIB_EXPORT DrawMode{
        Fill,
        Outline
    };
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
    void drawRectangle(float x, float y, float w, float h);

    /**
    * @brief draws an ellipse, if u want circle just pass same x and y radius
    * for triangle use segments = 3
    */
    void drawEllipse(float cx, float cy, float xr, float yr, int segments = 40);

    /**
    * @brief sets the fill color
    */
    void setFillColor(const Color& color);

    /**
    * @brief sets draw mode from Canvas::DrawMode enum
    */
    void setDrawMode(const DrawMode& drawMode);

    ~Canvas();

private:
    float xToGl(float x) const;
    float yToGl(float y) const;

    void applyColorGl();


private:
    CANVASLIB_SUPPRESS_C4251
    std::shared_ptr<GLFWwindow> mpWindowHandle;
    std::function<void(void)> mUpdateFunction;
    Color mFillColor;
    GLenum mDrawMode;
    Vec2<int> mSize;
};

}
