#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>

#include <stb_image.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include <fmt/core.h>
#include <fmt/color.h>

#include <string>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <ranges>
#include <vector>

#include "./shader.hpp"

namespace Magma {

std::vector<uint32_t> string_range(uint32_t start, uint32_t end, uint32_t factor = 1);

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec2 tex;
};

struct Texture {
    uint32_t id;
    uint32_t w;
    uint32_t h;
};

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

class Game
{
private:
    SDL_Window *m_window = nullptr;

    SDL_GLContext m_context = nullptr;

    float m_delta = 0.0f;

    void init();
    void close();

    Texture loadTexture(const std::string& path);
    void framebufferSizeCallback();

public:
    Game();
    ~Game();

    void run();
};

}

#endif

