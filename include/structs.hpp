#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <cstdint>
#include <glm/glm.hpp>

namespace Magma
{

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
    bool alpha;
};

}
#endif //LIBRARY_STRUCTS_HPP
