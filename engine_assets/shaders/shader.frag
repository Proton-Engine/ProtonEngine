#version 410 core

in vec2 textureCoordinate;

out vec3 color;

uniform sampler2D textureSampler;

void main() {
    color = texture(textureSampler, textureCoordinate).rgb;
}