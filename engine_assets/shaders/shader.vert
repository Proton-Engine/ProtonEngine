#version 410 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 modelNormal;
layout (location = 2) in vec2 vertexTextureCoordinate;

out vec2 textureCoordinate;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalModelMatrix;

void main() {
    mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition_modelspace, 1);
    textureCoordinate = vertexTextureCoordinate;
}