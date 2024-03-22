#pragma once

#include <string>
#include <functional>
#include <memory>

#include <RenderAbstraction.hpp>
#include <glad/glad.h>
#include "CanvasLib/Color.hpp"
#include "CanvasLib/Colors.hpp"
#include "CanvasLib/Vec2.hpp"
#include "CanvasLib/Window.hpp"
#include <GLFW/glfw3.h>

#define CANVASLIB_EXPORT

/**
 * The main namespace of the library (to keep my Vec2/Color away from your Vec2/Color)
 */
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

    Canvas(const Canvas&) = delete;
    Canvas(Canvas&&) = delete;
    auto operator=(const Canvas&) -> Canvas& = delete;
    auto operator=(Canvas&&) -> Canvas& = delete;

    /**
     * @brief Initializes the name field to the name of the project
     */
    Canvas(int32_t width, int32_t height);
    ~Canvas();

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
    void drawEllipse(float cx, float cy, float rx, float ry, int segments = 40);

    /**
    * @brief sets the fill color
    */
    void setFillColor(const Color& color);

    /**
    * @brief sets draw mode from Canvas::DrawMode enum
    */
    void setDrawMode(const DrawMode& drawMode);

private:
    [[nodiscard]] auto _xToGl(float x) const -> float;
    [[nodiscard]] auto _yToGl(float y) const -> float;

    void applyColorGl() const;

	std::unique_ptr<Window> m_Window;
    std::function<void(void)> m_UpdateFunction;
    Color m_FillColor;
    GLenum m_DrawMode;
    Vec2<int32_t> m_Size;
};

}
