#pragma once
#include "CanvasLib/Vec2.hpp"
#include <GLFW/glfw3.h>
#include <RenderAbstraction.hpp>
#include <cstdint>
#include <string>
#include <utility>

namespace canv
{

struct WindowProps
{
    std::string Title;
    uint32_t Width;
    uint32_t Height;

    explicit WindowProps(std::string title = "Canvas",
                         Vec2<uint32_t> size = { 1600, 900 })
        : Title(std::move(title)),
          Width(size.X),
          Height(size.Y)
    {
    }
};

class Window
{
public:
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    auto operator=(const Window&) -> Window& = delete;
    auto operator=(Window&&) -> Window& = delete;

    explicit Window(const WindowProps& props);
    virtual ~Window();

    void OnUpdate();

    [[nodiscard]] auto GetWidth() const -> uint32_t
    {
        return m_Data.Width;
    }
    [[nodiscard]] auto GetHeight() const -> uint32_t
    {
        return m_Data.Height;
    }

    [[nodiscard]] auto ShouldClose() const -> bool;

    // // Window attributes
    // void SetEventCallback(const EventCallbackFn& callback) override
    // {
    //     m_Data.EventCallback = callback;
    // }
    void SetVSync(bool enabled);
    [[nodiscard]] auto IsVSync() const -> bool;

    [[nodiscard]] virtual auto GetNativeWindow() const -> void*
    {
        return m_Handle;
    }

private:
    void _init(const WindowProps& props);

private:
    GLFWwindow* m_Handle;
    std::unique_ptr<Ra::RenderingContext> m_Context;

    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        // EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};
} // namespace canv
