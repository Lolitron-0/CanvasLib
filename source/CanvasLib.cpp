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

bool Canvas::s_ShouldRenderWatches{ true };
std::unique_ptr<std::thread> Canvas::s_WatchesRenderThread{ nullptr };
std::mutex Canvas::s_CustomWatchesMutex{};
std::unordered_map<std::string, std::string> Canvas::s_CustomWatches{};

Canvas::Canvas(uint32_t width, uint32_t height)
    : m_Size(width, height),
      m_FillColor(255, 255, 255),
      m_DrawMode(Ra::RendererAPI::DrawMode::Triangles)
{
    static bool instanceCreated{ false };
    if (instanceCreated)
    {
        std::cout << "Only one Canvas object is allowed" << std::endl;
        std::abort();
    }

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

    instanceCreated = true;
}

void Canvas::start()
{
    PROFILER_SCOPE("Main cycle");

    s_WatchesRenderThread = std::make_unique<std::thread>(
        [this]()
        {
            while (s_ShouldRenderWatches)
            {
                renderWatches();
                std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
            }
        });

    while (!m_Window->ShouldClose())
    {
        double fpsScale{};
        auto currentTime{ glfwGetTime() };
        auto deltaTime{ currentTime - m_LastFrameTime };
        fpsScale = (1.0 - glm::pow(0.95, deltaTime)) *
                   1e2; // coeff to scale velocity numbers
        m_LastFrameTime = currentTime;

        Ra::RenderCommand::SetClearColor({ 0, 0, 0, 1 });
        Ra::RenderCommand::Clear();

        Ra::Renderer2D::BeginScene(m_Projection);
        {
            PROFILER_SCOPE("Canvas - custom update")
            m_UpdateFunction(fpsScale);
        }

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
    // cx = _xToGl(cx);
    // cy = _yToGl(cy);
    // std::tie(rx, ry) = _normalizeSizeGl({ rx, ry }).AsTuple();
    //
    // float theta = 2 * 3.1415926F / static_cast<float>(segments);
    // float c = cosf(theta);
    // float s = sinf(theta);
    // float t{};
    //
    // float x = 1; // we start at angle = 0
    // float y = 0;
    //
    // applyColorGl();
    // glBegin(m_DrawMode);
    // for (int i = 0; i < segments; i++)
    // {
    //     glVertex2f(x * rx + cx, y * ry + cy);
    //
    //     t = x;
    //     x = c * x - s * y;
    //     y = s * t + c * y;
    // }
    // glEnd();
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
        m_DrawMode = Ra::RendererAPI::DrawMode::Triangles;
        break;
    case DrawMode::Outline:
        m_DrawMode = Ra::RendererAPI::DrawMode::LineLoop;
        break;
    default:
        break;
    }
}

Canvas::~Canvas()
{
    s_ShouldRenderWatches = false;
    s_WatchesRenderThread->join();
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

void Canvas::renderWatches()
{
    using namespace ftxui;
    static std::string resetPosition{};

    PROFILER_SCOPE("Canvas::renderTUI");

    auto stats{ Ra::Renderer2D::GetStats() };
    std::vector<std::vector<std::string>> tableData{ {
        { "FPS", std::to_string(
                     static_cast<int32_t>(std::round(stats.ScenesPerSecond))) },
        { "Draw calls", std::to_string(stats.DrawCalls) },
        { "Num indices", std::to_string(stats.Indices) },
    } };
    for (const auto& it : s_CustomWatches)
    {
        tableData.push_back({ it.first, it.second });
    }

    auto table{ Table{ tableData } };

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

void Canvas::disableWatches()
{
    s_ShouldRenderWatches = false;
}

void Canvas::enableWatches()
{
    s_ShouldRenderWatches = true;
}

void Canvas::setWatch(const std::string& key, const std::string& value)
{
    std::lock_guard lock{ s_CustomWatchesMutex };
    s_CustomWatches[key] = value;
}

void Canvas::removeWatch(const std::string& key)
{
    s_CustomWatches.erase(key);
}

} // namespace canv
