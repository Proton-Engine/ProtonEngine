#version 410 core

in vec2 textureCoordinate;
in vec3 fragNormal;
in vec3 worldPosition;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 lightPosition;

vec3 calculatePhongLighting();
vec3 calculatePhoneLightingDiffuseComponent(vec3 lightColor);

void main() {
    color = texture(textureSampler, textureCoordinate).rgb * calculatePhongLighting();
}

vec3 calculatePhongLighting()
{
    // TODO: Fix this light color input thingy
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    float ambient = 0.1f;

    vec3 diffuse = calculatePhoneLightingDiffuseComponent(lightColor);

    return ambient + diffuse;
}

vec3 calculatePhoneLightingDiffuseComponent(vec3 lightColor)
{
    vec3 directionToLight = normalize(lightPosition - worldPosition);
    // Dot product returns a value between -1 and 1, where -1 is an angle of 180 degreens and 1 is an angle of 1 degree.
    // The closer the direction to the light is to the normal, the more effect diffuse lighting has
    float diffuseMultiplier = max(dot(normalize(fragNormal), directionToLight), 0.0);

    return diffuseMultiplier * lightColor;
}