#include <cmath>
#include <iostream>
#include <string>

#include "CanvasLib/CanvasLib.hpp"

namespace canv
{

Canvas::Canvas(uint32_t width, uint32_t height)
    : m_Size(width, height),
      m_FillColor(255, 255, 255),
      m_DrawMode(GL_TRIANGLE_FAN)
{
    PROFILER_BEGIN_SESSION("CanvasLib session",
                           "ProfilingResult-CanvasLib.json");
    Ra::SetErrorCallback([](const auto& msg)
                         { std::cout << msg << std::endl; });
    Ra::SetLogCallback([](const auto& msg)
                       { std::cout << "[RA LOG]: " << msg << std::endl; });
	Ra::Init<Ra::Renderer2D>(Ra::RendererAPI::API::OpenGL);

    m_Window =

        std::make_unique<Ra::Window>(Ra::WindowProps{ "Canvas", { width, height } });

    glfwSetErrorCallback([](int /*errCode*/, const char* message)
                         { std::cerr << message << std::endl; });

    glOrtho(-1, 1., 1., -1, -1, 1);

    setUpdateFunction([]() {});

    // Ra::Renderer2D::ResizeViewport(
    //     { m_Window->GetWidth(), m_Window->GetHeight() });
}

void Canvas::start()
{
    PROFILER_SCOPE("Main cycle");
    while (!m_Window->ShouldClose())
    {
        glfwPollEvents();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // m_UpdateFunction();
		Ra::Renderer2D::DrawQuad({0,0},)
        m_Window->OnUpdate();
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
    std::tie(rx, ry) = _normalizeSizeGl({ rx, ry }).AsTuple();

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
    m_Window.reset(nullptr);
    glfwTerminate();
    PROFILER_END_SESSION();
}

auto Canvas::_xToGl(float x) const -> float
{
    return -1 + 2 * (x / m_Size.X);
}

auto Canvas::_yToGl(float y) const -> float
{
    return -1 + 2 * (y / m_Size.Y);
}

auto Canvas::_normalizeSizeGl(const Vec2f& size) const -> Vec2f
{
    return { 2 * size.X / m_Size.X, 2 * size.Y / m_Size.Y };
}

void Canvas::applyColorGl() const
{
    glColor4ub(m_FillColor.R, m_FillColor.G, m_FillColor.B, m_FillColor.A);
}

} // namespace canv
