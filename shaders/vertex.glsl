#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

out vec3 bPos;
out vec3 bCol;
out vec2 bTex;

void main() 
{
    bPos = aPos;
    bCol = aCol;
    bTex = aTex;

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
