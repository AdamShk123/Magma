#define STB_IMAGE_IMPLEMENTATION
#include "../include/game.hpp"

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

Game::Game()
{
    init();
}

Game::~Game() 
{
    close();
}

void Game::init() 
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    SDL_DisplayMode dm{};
    
    int success = SDL_GetCurrentDisplayMode(0, &dm);

    int width = 1920;
    int height = 1080;

    if(success == 0) 
    {
        width = dm.w;
        height = dm.h;
    }
    else 
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }

    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    m_window = SDL_CreateWindow("Frozen Moonlight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
    if(!m_window)
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }

    m_context = SDL_GL_CreateContext(m_window);
    if(!m_context)
    {
        std::string error = SDL_GetError();
        throw std::runtime_error(error.c_str());
    }

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) 
    {
        std::string error = "Failed to initialize GLAD!";
        throw std::runtime_error(error.c_str());
    }

    auto flags = (IMG_InitFlags)IMG_INIT_JPG | IMG_INIT_PNG;
    auto result = IMG_Init(flags);
    if(result != flags)
    {
        std::string error = IMG_GetError();
        throw std::runtime_error(error.c_str());
    }

    glViewport(0,0,width,height);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, nullptr);
}

void Game::run() 
{
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    uint32_t VAO, VBO, EBO;

    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

    glCreateBuffers(1, &EBO);
    glNamedBufferStorage(EBO, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);

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

    shader.use();

    SDL_Event e;

    bool quit = false;

    while(!quit)
    {
        auto start_time = SDL_GetTicks();

        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type) 
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                framebufferSizeCallback();
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

        // glNamedBufferSubData(VBO, 0, sizeof(vertices), &vertices);
        // glNamedBufferSubData(EBO, 0, sizeof(indices), &indices);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

        SDL_GL_SwapWindow(m_window);

        auto stop_time = SDL_GetTicks();

        m_delta = (stop_time - start_time) / 1000.0f;
    }
}

void Game::close() 
{
    IMG_Quit();

    SDL_GL_DeleteContext(m_context);
    m_context = nullptr;

    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_Quit();
}

void Game::framebufferSizeCallback() 
{
    int w,h;
    SDL_GetWindowSize(m_window,&w,&h);
    glViewport(0,0,w,h);
}
