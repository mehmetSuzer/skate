
#version 330 core

struct Light {
    vec3 color;
    vec3 position;
};

out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec3 cameraPosition;
uniform Light light;
uniform vec4 color;

void main() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float a = 0.2f;
    float b = 0.7f;
    float attenuation = 1.0f / ((a * distanceToLight + b) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? 0.5f * pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    FragColor = color * vec4(light.color, 1.0f) * attenuation * (ambientPower + diffusePower + specularPower);
}
