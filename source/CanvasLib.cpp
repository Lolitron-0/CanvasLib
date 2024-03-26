#include <cmath>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>

#include "CanvasLib/CanvasLib.hpp"

namespace canv
{

bool Canvas::s_ShouldRenderTui{ true };
std::unique_ptr<std::thread> Canvas::s_TuiRenderThread{ nullptr };

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

    m_Window = std::make_unique<Ra::Window>(
        Ra::WindowProps{ "Canvas", { width, height } });
    m_Window->SetVSync(false);

    glfwSetErrorCallback([](int /*errCode*/, const char* message)
                         { std::cerr << message << std::endl; });

    glOrtho(-1, 1., 1., -1, -1, 1);
    m_Projection = glm::ortho(0.F, static_cast<float>(m_Size.X),
                              static_cast<float>(m_Size.Y), 0.F);

    setUpdateFunction([](double) {});

    // Ra::Renderer2D::ResizeViewport(
    //     { m_Window->GetWidth(), m_Window->GetHeight() });
}

void Canvas::start()
{
    PROFILER_SCOPE("Main cycle");

    s_TuiRenderThread = std::make_unique<std::thread>(
        [this]()
        {
            while (s_ShouldRenderTui)
            {
                renderTUI();
                std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
            }
        });

    while (!m_Window->ShouldClose())
    {
		auto currentTime{glfwGetTime()};
        auto deltaTime{ currentTime - m_LastFrameTime };
		auto fpsScale{1.0 - glm::pow(0.95, deltaTime) };
		m_LastFrameTime = currentTime;

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        Ra::Renderer2D::BeginScene(m_Projection);
        m_UpdateFunction(fpsScale);

        // Ra::Renderer2D::DrawQuad({ 100, 200 }, { 100, 300 }, { 1.0, 0, 0, 1
        // });
        Ra::Renderer2D::EndScene();
        m_Window->OnUpdate();
        glfwPollEvents();
    }
}

void Canvas::setUpdateFunction(std::function<void(double)> upd)
{
    m_UpdateFunction = std::move(upd);
}

void Canvas::drawRectangle(float x, float y, float w, float h)
{
    Ra::Renderer2D::DrawQuad({ x, y }, { w, h }, m_FillColor);
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
    s_ShouldRenderTui = false;
    s_TuiRenderThread->join();
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

void Canvas::renderTUI()
{
    using namespace ftxui;
    static std::string resetPosition{};

    PROFILER_SCOPE("Canvas::renderTUI");

    auto stats{ Ra::Renderer2D::GetStats() };
    auto table{ Table({
        { "FPS", std::to_string(
                     static_cast<int32_t>(std::round(stats.ScenesPerSecond))) },
        { "Draw calls", std::to_string(stats.DrawCalls) },
        { "Num indices", std::to_string(stats.Indices) },
    }) };

    table.SelectColumn(0).Decorate(bold);

    table.SelectColumn(1).Decorate(flex);

    table.SelectAll().SeparatorVertical();
    table.SelectAll().Border();
    table.SelectAll().DecorateCellsAlternateRow(color(ftxui::Color::White), 3,
                                                0);
    table.SelectAll().DecorateCellsAlternateRow(color(ftxui::Color::Cyan), 3,
                                                1);
    table.SelectAll().DecorateCellsAlternateRow(color(ftxui::Color::Blue), 3,
                                                2);

    // clang-format off
    auto document =
	vbox({
        text("CanvasLib Info") | border | flex,
		table.Render()     
	});
    // clang-format on

    auto screen = Screen::Create(Dimension::Full(),       // Width
                                 Dimension::Fit(document) // Height
    );
    Render(screen, document);

    std::cout << resetPosition;
    screen.Print();
    resetPosition = screen.ResetPosition();
}

void Canvas::DisableStats()
{
    s_ShouldRenderTui = false;
}

void Canvas::EnableStats()
{
    s_ShouldRenderTui = true;
}
} // namespace canv
