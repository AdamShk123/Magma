#version 460 core

in vec3 attribCol;
in vec2 attribTex;

uniform sampler2D texture0;
uniform sampler2D texture1;

out vec4 FragColor;

void main() 
{
    FragColor = mix(texture(texture0, attribTex),
                    texture(texture1, attribTex), 0.8);
}
