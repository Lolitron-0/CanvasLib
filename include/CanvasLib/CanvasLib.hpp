#pragma once

#include <functional>
#include <memory>
#include <string>

#include "CanvasLib/Color.hpp"
#include "CanvasLib/Colors.hpp"
#include "CanvasLib/Vec2.hpp"
#include <GLFW/glfw3.h>
#include <RenderAbstraction.hpp>
#include <glad/glad.h>

#define CANVASLIB_EXPORT

/**
 * @mainpage CanvasLib
 * This is a 2D rendering library for fast protoryping (or just playing around)
inspired by JavaScript canvas. It runs on OpenGL (Ra library to be exact). For
now CanvasLib only supports one instance of canvas (one window).
 * Here is a basic usage example:
 * @code{.cpp}
 * #include <CanvasLib/CanvasLib.hpp>
 *
 * auto main() -> int
 * {
 *     canv::Canvas canvas{ 1000, 800 };
 *     canvas.setUpdateFunction(
 *         [&canvas](double fpsScale)
 *         {
 *             canvas.setFillColor(canv::Colors::green);
 *             canvas.drawRectangle(100, 100, 50, 150);
 *         });
 *     canvas.start();
 * }
 * @endcode
*/

/**
 * Main namespace of the library (to keep my Vec2/Color away from your
 * Vec2/Color)
 */
namespace canv
{

/**
 * @brief The main class representing the canvas.
 * To use it you only need to:
 * - create Canvas object
 * - specify update function (setUpdateFunction() method)
 * - call start() method
 * @note There can only be one Canvas object
 */
class CANVASLIB_EXPORT Canvas
{
public:
    enum class DrawMode
    {
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
    Canvas(uint32_t width, uint32_t height);
    ~Canvas();

    /**
     * @brief starts the main window cycle IN MAIN THREAD
     */
    void start();
    /**
     * @brief sets update function that will be called every frame
     * @param upd function (or lambda) with void(double) signature. Double
     * parameter is fps scale factor
     */
    void setUpdateFunction(std::function<void(double)> upd);

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
     * @brief Enables rendering watches in  terminal
     */
    static void enableWatches();
    /**
     * @brief Disables rendering watches in  terminal
     */
    static void disableWatches();
    /**
     * @brief Adds or updates entry in watches table
	 *
     * Watches allow you to add rows to the table in terminal interface (one that contains
     * rendering statistics by default)
     */
    static void setWatch(const std::string& key, const std::string& value);
    /**
     * @brief Removes entry from watches table, does nothing if it doesn't exist
	 * @note Default entries can't be deleted
     */
    static void removeWatch(const std::string& key);

private:
    [[nodiscard]] auto _xToGl(float x) const -> float;
    [[nodiscard]] auto _yToGl(float y) const -> float;
    [[nodiscard]] auto _normalizeSizeGl(const Vec2f& size) const -> Vec2f;

    static void renderWatches();
    static bool s_ShouldRenderWatches;
    static std::unique_ptr<std::thread> s_WatchesRenderThread;
    static std::mutex s_CustomWatchesMutex;
    static std::unordered_map<std::string, std::string> s_CustomWatches;

    void applyColorGl() const;

    std::unique_ptr<Ra::Window> m_Window;
    std::function<void(double)> m_UpdateFunction;
    Color m_FillColor;
    Vec2<uint32_t> m_Size;
    glm::mat4 m_Projection;
    double m_LastFrameTime;
};

} // namespace canv
