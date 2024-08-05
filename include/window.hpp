#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL_video.h>

#include <glad/glad.h>

#include <optional>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace Magma
{

class Window
{
private:
    SDL_Window *m_window = nullptr;
    SDL_GLContext m_context = nullptr;

    std::optional<SDL_DisplayMode> getDisplaySize();
    void setGLFlags();
    std::optional<std::string> initWindow(const SDL_DisplayMode& dm);
    std::optional<std::string> initWindow(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height, SDL_WindowFlags flags);
    std::optional<std::string> initGLContext();
public:
    Window();
    Window(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height, SDL_WindowFlags flags);

    ~Window();

    void swapWindow();
    void refreshViewport();
};

}

#endif
