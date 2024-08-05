#define STB_IMAGE_IMPLEMENTATION
#include "../include/game.hpp"

namespace Magma {

std::optional<std::string> initSDL()
{
    return SDL_Init(SDL_INIT_VIDEO) < 0 ? std::optional<std::string>(SDL_GetError()) : std::nullopt;
};

std::optional<std::string> initGLAD()
{
    return !gladLoadGLLoader(SDL_GL_GetProcAddress) ? std::optional<std::string>(SDL_GetError()) : std::nullopt;
};

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fmt::rgb color {};
    std::string typeString {};
    std::string severityString {};

    switch(type) {
        case GL_DEBUG_TYPE_ERROR:
            color = fmt::rgb(0xFF0000);
            typeString = "GL_DEBUG_TYPE_ERROR";
            break;
        case GL_DEBUG_TYPE_OTHER:
            color = fmt::rgb(0x707070);
            typeString = "GL_DEBUG_TYPE_OTHER";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            color = fmt::rgb(0xFCC203);
            typeString = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            color = fmt::rgb(0x9003fc);
            typeString = "GL_DEBUG_TYPE_PERFORMANCE";
            break;
        default:
            color = fmt::rgb(0x707070);
            break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            severityString = "GL_DEBUG_SEVERITY_HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityString = "GL_DEBUG_SEVERITY_MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityString = "GL_DEBUG_SEVERITY_LOW";
            break;
        default:
            severityString = "GL_DEBUG_SEVERITY_OTHER";
            break;
    }

    std::string output = fmt::format(fmt::fg(color), "GL CALLBACK: type = {}, severity = {}, message = {},", typeString, severityString, message);
    fmt::println("{}", output);
}

void enableGLDebugOutput()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, nullptr);
}

Game::Game() : m_window()
{
    std::optional<std::string> initGLAD_success = initGLAD();
    if(initGLAD_success.has_value())
    {
        fmt::println("{}", initGLAD_success.value());
    }
//    if(SDL_GL_SetSwapInterval(0) == -1)
//    {
//        std::string error = SDL_GetError();
//        fmt::println("{}", error);
//    }
}

Game::~Game()
{
    SDL_Quit();
}

std::optional<std::string> initMagma()
{
    std::optional<std::string> initSDL_success = initSDL();
    if(initSDL_success.has_value())
    {
        return initSDL_success;
    }
    return std::nullopt;
}

std::optional<Texture> loadTexture(const std::string& path)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    bool alpha = nrChannels == RGBA;

    uint32_t id;
    glCreateTextures(GL_TEXTURE_2D, 1, &id);

    if(data)
    {
        glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (alpha)
        {
            glTextureStorage2D(id, 1, GL_RGBA8, width, height);
            glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTextureStorage2D(id, 1, GL_RGBA8, width, height);
            glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        }

        glGenerateTextureMipmap(id);

        stbi_image_free(data);

        return Texture {id, static_cast<uint32_t>(width), static_cast<uint32_t>(height), alpha};
    }
    return std::nullopt;
}

void Game::run()
{
    glEnable(GL_DEPTH_TEST);

    std::vector<Vertex> vertices {};
    std::vector<uint32_t> indices {};

    vertices = VERTICES;
    indices = INDICES;

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    uint32_t VAO, VBO, EBO;

    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &EBO);
    glNamedBufferStorage(EBO, indices.size() * sizeof(uint32_t), indices.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &VAO);

    uint32_t binding_point =  0;
    glVertexArrayVertexBuffer(VAO, binding_point, VBO, 0, sizeof(Vertex));

    uint32_t aPos = 0;
    uint32_t aCol = 1;
    uint32_t aTex = 2;

    glEnableVertexArrayAttrib(VAO, aPos);
    glEnableVertexArrayAttrib(VAO, aCol);
    glEnableVertexArrayAttrib(VAO, aTex);

    glVertexArrayAttribFormat(VAO, aPos, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
    glVertexArrayAttribFormat(VAO, aCol, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, col));
    glVertexArrayAttribFormat(VAO, aTex, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex));

    glVertexArrayAttribBinding(VAO, aPos, binding_point);
    glVertexArrayAttribBinding(VAO, aCol, binding_point);
    glVertexArrayAttribBinding(VAO, aTex, binding_point);

    glVertexArrayElementBuffer(VAO, EBO);

    std::string imagePath = "textures/awesomeface.png";
    std::optional<Texture> t0 = loadTexture(imagePath);

    imagePath = "textures/container.jpg";
    std::optional<Texture> t1 = loadTexture(imagePath);

    glBindTextureUnit(0, t0->id);
    glBindTextureUnit(1, t1->id);

    shader.use();

    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f));

    auto view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1200.0f, 0.1f, 100.0f);

    SDL_Event e;

    bool quit = false;

    while(!quit)
    {
        uint32_t start_time = SDL_GetTicks();

        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    m_window.refreshViewport();
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (e.key.keysym.sym)
                    {
                    }
                    break;
            }
        }

        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setInt("texture0", 0);
        shader.setInt("texture1", 1);

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("proj", proj);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        m_window.swapWindow();

        uint32_t stop_time = SDL_GetTicks();

//        fmt::println("fps: {}", 1.0f / ((float)(stop_time - start_time) / 1000.0f));

        m_delta = (float)(stop_time - start_time) / 1000.0f;
    }
}

}


