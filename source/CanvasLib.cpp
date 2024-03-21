#include <cmath>
#include <iostream>
#include <string>

#include "CanvasLib/CanvasLib.hpp"

namespace canv
{

Canvas::Canvas(int32_t width, int32_t height)
    : m_Size(width, height),
      m_FillColor(255, 255, 255),
      m_DrawMode(GL_TRIANGLE_FAN)
{
    glfwInit();
    this->m_WindowHandle.reset(
        glfwCreateWindow(width, height, "", nullptr, nullptr),   // new value
        [](GLFWwindow* ptr) { return glfwDestroyWindow(ptr); }); // deleter
    glfwMakeContextCurrent(m_WindowHandle.get());
    glfwSetErrorCallback([](int /*errCode*/, const char* message)
                         { std::cerr << message << std::endl; });
    glOrtho(0, 1., 1., 0, -1, 1);

    setUpdateFunction([]() {});
}

void Canvas::start()
{
    while (!glfwWindowShouldClose(m_WindowHandle.get()))
    {
        glfwPollEvents();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        m_UpdateFunction();
        glfwSwapBuffers(m_WindowHandle.get());
    }
}

void Canvas::setUpdateFunction(std::function<void()> upd)
{
    m_UpdateFunction = std::move(upd);
}

void Canvas::drawRectangle(float x, float y, float w, float h)
{
    applyColorGl();
    glBegin(m_DrawMode);
    glVertex2f(_xToGl(x), _yToGl(y));
    glVertex2f(_xToGl(x + w), _yToGl(y));
    glVertex2f(_xToGl(x + w), _yToGl(y + h));
    glVertex2f(_xToGl(x), _yToGl(y + h));
    // glRectf(xToGl(x), yToGl(y), xToGl(x+w), yToGl(y+h));
    glEnd();
}

void Canvas::drawEllipse(float cx, float cy, float rx, float ry, int segments)
{
    cx = _xToGl(cx);
    cy = _yToGl(cy);
    rx = _xToGl(rx);
    ry = _yToGl(ry);

    float theta = 2 * 3.1415926F / static_cast<float>(segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t{};

    float x = 1; // we start at angle = 0
    float y = 0;

    applyColorGl();
    glBegin(m_DrawMode);
    for (int i = 0; i < segments; i++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);

        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void Canvas::setFillColor(const Color& color)
{
    m_FillColor = color;
}

void Canvas::setDrawMode(const DrawMode& drawMode)
{
    switch (drawMode)
    {
    case DrawMode::Fill:
        m_DrawMode = GL_TRIANGLE_FAN;
        break;
    case DrawMode::Outline:
        m_DrawMode = GL_LINE_LOOP;
        break;
    default:
        break;
    }
}

Canvas::~Canvas()
{
    m_WindowHandle.reset();
    glfwTerminate();
}

auto Canvas::_xToGl(float x) const -> float
{
    return x / m_Size.X;
}

auto Canvas::_yToGl(float y) const -> float
{
    return y / m_Size.Y;
}

void Canvas::applyColorGl() const
{
    glColor4ub(m_FillColor.R, m_FillColor.G, m_FillColor.B, m_FillColor.A);
}

} // namespace canv
