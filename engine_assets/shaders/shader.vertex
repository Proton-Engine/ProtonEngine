#version 410 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 modelNormal;
layout(location = 2) in vec2 vertexTextureCoordinate;

out vec2 textureCoordinate;
out vec3 normal;
out vec3 fragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalModelMatrix;

void main(){
    mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    textureCoordinate = vertexTextureCoordinate;
    normal = mat3(normalModelMatrix) * modelNormal;
    fragPos = vec3(modelMatrix * vec4(vertexPosition_modelspace, 1.0));
}