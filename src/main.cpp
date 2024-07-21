#include "../include/main.hpp"

int main(int argc, char *argv[])
{
    fmt::println("Hello There!");

    auto game = Magma::Game();

    game.run();

    fmt::println("Goodbye There!");

    return 0;
}
