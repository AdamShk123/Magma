#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>

#include <stb_image.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fmt/core.h>
#include <fmt/color.h>

#include <string>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <ranges>
#include <vector>
#include <optional>

#include "./shader.hpp"
#include "./window.hpp"
#include "./structs.hpp"

namespace Magma {

#define RGBA 4

const std::vector<Vertex> VERTICES {
        {{-0.5f, -0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}, {1.0f, 1.0f}},
};

const std::vector<uint32_t> INDICES {
        0,1,2,
        1,2,3
};

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

/// \details loadTexture receives a string containing
/// the path to a texture file in the project,
/// which it loads into memory and returns a
/// struct of type Texture, containing the ID
/// given to the loaded texture and the width
/// and height of it.
///
/// \param path path to texture file that should be loaded into memory
/// \return Texture struct containing ID of loaded texture, width, and height
std::optional<Texture> loadTexture(const std::string& path);

std::optional<std::string> initMagma();
void enableGLDebugOutput();

class Game
{
private:
    float m_delta = 0.0f;

    Window m_window;
public:
    Game();
    ~Game();

    void run();
};

}

#endif

