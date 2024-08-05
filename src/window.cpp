#include "../include/window.hpp"

namespace Magma
{

Window::Window()
{
    std::optional<SDL_DisplayMode> dm = getDisplaySize();
    if(!dm.has_value())
    {
        throw std::runtime_error(SDL_GetError());
    }

    std::optional<std::string> initWindow_success = initWindow(dm.value());
    if(initWindow_success.has_value())
    {
        throw std::runtime_error(initWindow_success.value());
    }

    std::optional<std::string> initGLContext_success = initGLContext();
    if(initGLContext_success.has_value())
    {
        throw std::runtime_error(initGLContext_success.value());
    }
}

Window::Window(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height, SDL_WindowFlags flags)
{
    std::optional<std::string> initWindow_success = initWindow(title, x, y, width, height, flags);
    if(initWindow_success.has_value())
    {
        throw std::runtime_error(initWindow_success.value());
    }

    std::optional<std::string> initGLContext_success = initGLContext();
    if(initGLContext_success.has_value())
    {
        throw std::runtime_error(initGLContext_success.value());
    }
}

Window::~Window()
{
    SDL_GL_DeleteContext(m_context);
    m_context = nullptr;

    SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

std::optional<SDL_DisplayMode> Window::getDisplaySize()
{
    SDL_DisplayMode dm{};

    int success = SDL_GetCurrentDisplayMode(0, &dm);

    return success == 0 ? std::optional<SDL_DisplayMode>(dm) : std::nullopt;
}

void Window::setGLFlags()
{
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
}

std::optional<std::string> Window::initWindow(const SDL_DisplayMode& dm)
{
    setGLFlags();

    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    m_window = SDL_CreateWindow("Frozen Moonlight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h, window_flags);

    return m_window ? std::nullopt : std::optional<std::string>(SDL_GetError());
}

std::optional<std::string> Window::initWindow(const std::string title, const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const SDL_WindowFlags flags)
{
    setGLFlags();

    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);

    return m_window ? std::nullopt : std::optional<std::string>(SDL_GetError());
}

std::optional<std::string> Window::initGLContext()
{
    m_context = SDL_GL_CreateContext(m_window);
    return m_context ? std::nullopt : std::optional<std::string>(SDL_GetError());
}

void Window::swapWindow()
{
    SDL_GL_SwapWindow(m_window);
}

void Window::refreshViewport()
{
    int w,h;
    SDL_GetWindowSize(m_window,&w,&h);
    glViewport(0,0,w,h);
}

}
