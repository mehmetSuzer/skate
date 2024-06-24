
#version 330 core

struct MaterialMap {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 color;
    vec3 position;
};

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 tex;

uniform vec3 cameraPosition;
uniform Light light;
uniform MaterialMap materialMap;

void main() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float a = 0.2f;
    float b = 0.7f;
    float lightIntensity = 1.0f / ((a * distanceToLight + b) * distanceToLight + 1.0f);

    float ambientPower = 0.15f;
    vec4 ambient = texture(materialMap.diffuse, tex) * ambientPower;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    vec4 diffuse = texture(materialMap.diffuse, tex) * diffusePower;
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), materialMap.shininess) : 0.0f;
    vec4 specular = vec4(texture(materialMap.specular, tex).rrr, 1.0f) * specularPower;

    // emissionPower is calculated in this way just to remove all emission on the steel part of the container.
    float emissionPower = (texture(materialMap.specular, tex).r == 0.0f) ? 1.0f : 0.0f;
    vec4 emission = texture(materialMap.emission, tex) * emissionPower;

    FragColor = emission + vec4(light.color, 1.0f) * (ambient + lightIntensity * (diffuse + specular));
}
