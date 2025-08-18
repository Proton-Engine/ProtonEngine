/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "window.h"

#include "protonengine/common/event_bus.h"

#include "protonengine/common/logger.h"
#include "protonengine/renderer/irenderer.h"

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <format>

namespace ProtonEngine::Core
{

Window::Window(int32_t width, int32_t height, std::string_view title, Renderer::IRenderer & renderer)
{
    PROTON_LOG_INFO(std::format("Creating window of size {}x{} with title {}", width, height, title));
    if (!glfwInit())
    {
        const char * description;
        glfwGetError(&description);
        PROTON_LOG_ERROR(std::format("Failed to initialize glfw with error: {}", description));
        exit(EXIT_FAILURE);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_windowHandle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(m_windowHandle);

    renderer.setWindowContext([](const char * proc_name) { return (void *)glfwGetProcAddress(proc_name); });

    m_uiContext = std::make_unique<Ui::UiContext>(m_windowHandle);
    registerCallbacks();

    glfwSwapInterval(0); // Disable vsync

    Common::EventBus::fireEvent(Common::Event::WINDOW_RESIZE_EVENT, Common::WindowResizeEventContext{width, height});
}

Window::~Window()
{
    glfwDestroyWindow(m_windowHandle);
}

auto Window::update() noexcept -> bool
{
    if (glfwWindowShouldClose(m_windowHandle) ||
        glfwGetKey(m_windowHandle, GLFW_KEY_ESCAPE))
    {
        glfwTerminate();
        return false;
    }

    glfwSwapBuffers(m_windowHandle);
    glfwPollEvents();
    return true;
}

void Window::registerCallbacks() const
{
    glfwSetKeyCallback(m_windowHandle, [](GLFWwindow * /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
        if (action == GLFW_REPEAT)
            return;

        Common::KeyEventEventContext context{
            .key = static_cast<Common::Key>(key),
            .state = action == GLFW_PRESS ? Common::KeyState::PRESSED : Common::KeyState::RELEASED};
        Common::EventBus::fireEvent(Common::Event::KEY_EVENT, context);
    });

    glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow *, const int newWidth, const int newHeight) {
        Common::EventBus::fireEvent(Common::Event::WINDOW_RESIZE_EVENT, Common::WindowResizeEventContext{newWidth, newHeight});
    });
}

} // namespace ProtonEngine::Core