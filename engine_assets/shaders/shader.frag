#version 410 core

struct Material {
    vec3 baseColor;
    sampler2D baseTexture;
    vec3 specularColor;
    sampler2D specularMap;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
};

in vec2 textureCoordinate;
in vec3 fragNormal;
in vec3 worldPosition;
//in vec3 lightPositionFrag;

out vec3 color;

uniform Material material;
// The light parameters should be passed in view space (so multiplied by the view and model matrix)
uniform Light directionalLight;

vec3 calculatePhongLighting();
vec3 calculatePhoneLightingDiffuseComponent(vec3 lightDirection, vec3 lightColor);
vec3 calculatePhongLightingSpecularComponent(vec3 lightDirection, vec3 lightColor);

void main() {
    color = texture(material.baseTexture, textureCoordinate).rgb * calculatePhongLighting();
}

vec3 calculatePhongLighting()
{
    // TODO: Fix this light color input thingy
    //    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightColor = directionalLight.color;

    vec3 ambient = 0.1f * material.baseColor;

    //    vec3 diffuse = calculatePhoneLightingDiffuseComponent(lightPositionFrag - worldPosition, lightColor);
    vec3 diffuse = calculatePhoneLightingDiffuseComponent(-directionalLight.direction, lightColor);
    vec3 specular = calculatePhongLightingSpecularComponent(-directionalLight.direction, lightColor);

    return ambient + diffuse + specular;
}

vec3 calculatePhoneLightingDiffuseComponent(vec3 lightDirection, vec3 lightColor)
{
    vec3 directionToLight = normalize(lightDirection);
    // Dot product returns a value between -1 and 1, where -1 is an angle of 180 degreens and 1 is an angle of 1 degree.
    // The closer the direction to the light is to the normal, the more effect diffuse lighting has
    float diffuseMultiplier = max(dot(normalize(fragNormal), directionToLight), 0.0);

    return diffuseMultiplier * lightColor * material.baseColor;
}

vec3 calculatePhongLightingSpecularComponent(vec3 lightDirection, vec3 lightColor)
{
    vec3 directionToLight = normalize(lightDirection);

    vec3 viewDir = normalize(-worldPosition);
    vec3 reflectDir = reflect(-directionToLight, normalize(fragNormal));

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    return spec * lightColor * material.specularColor * texture(material.specularMap, textureCoordinate).rgb;
}