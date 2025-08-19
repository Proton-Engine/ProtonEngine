#version 410 core

in vec2 textureCoordinate;
in vec3 fragNormal;
in vec3 worldPosition;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

vec3 calculatePhongLighting();
vec3 calculatePhoneLightingDiffuseComponent(vec3 lightColor);
vec3 calculatePhongLightingSpecularComponent(vec3 lightColor);

void main() {
    color = texture(textureSampler, textureCoordinate).rgb * calculatePhongLighting();
}

vec3 calculatePhongLighting()
{
    // TODO: Fix this light color input thingy
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    float ambient = 0.1f;

    vec3 diffuse = calculatePhoneLightingDiffuseComponent(lightColor);
    vec3 specular = calculatePhongLightingSpecularComponent(lightColor);

    return ambient + diffuse + specular;
}

vec3 calculatePhoneLightingDiffuseComponent(vec3 lightColor)
{
    vec3 directionToLight = normalize(lightPosition - worldPosition);
    // Dot product returns a value between -1 and 1, where -1 is an angle of 180 degreens and 1 is an angle of 1 degree.
    // The closer the direction to the light is to the normal, the more effect diffuse lighting has
    float diffuseMultiplier = max(dot(normalize(fragNormal), directionToLight), 0.0);

    return diffuseMultiplier * lightColor;
}

vec3 calculatePhongLightingSpecularComponent(vec3 lightColor)
{
    float specularStrength = 1;
    vec3 directionToLight = normalize(lightPosition - worldPosition);

    vec3 viewDir = normalize(cameraPosition - worldPosition);
    vec3 reflectDir = reflect(-directionToLight, normalize(fragNormal));

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return specularStrength * spec * lightColor;
}