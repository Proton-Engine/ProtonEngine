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
    float intensity;
};

in vec2 textureCoordinate;
in vec3 fragNormal;
in vec3 worldPosition;
in Light pointLightFrag;

out vec3 color;

uniform Material material;
// The light parameters should be passed in view space (so multiplied by the view and model matrix)
uniform Light directionalLight;

vec3 calculatePhongLighting();
vec3 calculatePhongLightingDiffuseComponent(vec3 lightDirection, vec3 lightColor, float attenuation);
vec3 calculatePhongLightingSpecularComponent(vec3 lightDirection, vec3 lightColor, float attenuation);
float attenuatateCusp(float distance, float radius, float max_intensity, float falloff);

void main() {
    color = texture(material.baseTexture, textureCoordinate).rgb * calculatePhongLighting();
}

vec3 calculatePhongLighting()
{
    vec3 ambient = 0.1f * material.baseColor;

    vec3 diffuse = calculatePhongLightingDiffuseComponent(-directionalLight.direction, directionalLight.color, 1);
    vec3 specular = calculatePhongLightingSpecularComponent(-directionalLight.direction, directionalLight.color, 1);

    float distance = length(pointLightFrag.position - worldPosition);
    float attenuation = attenuatateCusp(distance, pointLightFrag.intensity, 1.0, 1.0);

    diffuse += calculatePhongLightingDiffuseComponent(pointLightFrag.position - worldPosition, pointLightFrag.color, attenuation);
    specular += calculatePhongLightingSpecularComponent(pointLightFrag.position - worldPosition, pointLightFrag.color, attenuation);

    return ambient + diffuse + specular;
}

vec3 calculatePhongLightingDiffuseComponent(vec3 lightDirection, vec3 lightColor, float attenuation)
{
    vec3 directionToLight = normalize(lightDirection);
    // Dot product returns a value between -1 and 1, where -1 is an angle of 180 degreens and 1 is an angle of 1 degree.
    // The closer the direction to the light is to the normal, the more effect diffuse lighting has
    float diffuseMultiplier = max(dot(normalize(fragNormal), directionToLight), 0.0);

    return diffuseMultiplier * lightColor * material.baseColor * attenuation;
}

vec3 calculatePhongLightingSpecularComponent(vec3 lightDirection, vec3 lightColor, float attenuation)
{
    vec3 directionToLight = normalize(lightDirection);

    vec3 viewDir = normalize(-worldPosition);
    vec3 reflectDir = reflect(-directionToLight, normalize(fragNormal));

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    return spec * lightColor * material.specularColor * texture(material.specularMap, textureCoordinate).rgb * attenuation;
}

// Attenuation function from here: https://lisyarus.github.io/blog/posts/point-light-attenuation.html
float attenuatateCusp(float distance, float radius,
                      float max_intensity, float falloff)
{
    float s = distance / radius;

    if (s >= 1.0)
    return 0.0;

    float s2 = s * s;

    return max_intensity * ((1 - s2) * (1 - s2)) / (1 + falloff * s);
}