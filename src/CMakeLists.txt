find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(${PROJECT_NAME} glad.cpp main.cpp game.cpp window.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SDL2::SDL2 glm::glm)