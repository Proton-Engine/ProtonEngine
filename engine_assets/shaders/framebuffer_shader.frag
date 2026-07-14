#version 410 core

uniform sampler2D framebufferTexture;

in vec2 textureCoordinate;
out vec4 color;

void main()
{
    color = texture(framebufferTexture, textureCoordinate);
}