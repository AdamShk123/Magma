enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(tests main.cpp ../src/game.cpp ../src/glad.cpp ../src/window.cpp)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock fmt::fmt SDL2::SDL2 glm::glm)

include(GoogleTest)
gtest_discover_tests(tests)