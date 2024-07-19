#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>

#include "./shader.hpp"

#include "./stb_image.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>

#include <fmt/core.h>
#include <fmt/color.h>

#include <string>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <cstdint>

struct Vertex 
{
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec2 tex;
};

const Vertex vertices[] = {
    {{-0.5f, -0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}},
    {{0.0f, 0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}},
};

const uint32_t indices[] = {
    0,1,2
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
    void framebufferSizeCallback();

public:
    Game();
    ~Game();
    
    void run();
};

#endif

