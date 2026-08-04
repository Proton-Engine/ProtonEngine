#version 410 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTextureCoordinate;

out vec2 textureCoordinate;

void main() {
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0);
    textureCoordinate = vertexTextureCoordinate;
}