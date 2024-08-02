#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

out vec3 attribCol;
out vec2 attribTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
    attribCol = aCol;
    attribTex = aTex;

    gl_Position = proj * view * model * vec4(aPos.x, aPos.y * -1, aPos.z, 1.0f);
}
