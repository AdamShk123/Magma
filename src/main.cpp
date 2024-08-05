#include "../include/main.hpp"

int main(int argc, char *argv[])
{
    fmt::println("Hello There!");

    std::optional<std::string> success = Magma::initMagma();
    if(success.has_value())
    {
        throw std::runtime_error(success.value());
    }

    auto game = Magma::Game();

    game.run();

    fmt::println("Goodbye There!");

    return 0;
}
