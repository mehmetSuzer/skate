
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out vec4 lightingColor;

uniform mat4 model;
uniform mat4 projectionView;
uniform mat3 normalMatrix;

uniform vec3 cameraPosition;
uniform vec4 lightColor;
uniform vec3 lightPosition;

void main() {
    vec3 position = vec3(model * vec4(aPosition, 1.0f));
    gl_Position = projectionView * vec4(position, 1.0f);
    vec3 normal = normalMatrix * aNormal;

    vec3 positionToLightPosition = lightPosition - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float a = 0.2f;
    float b = 0.7f;
    float lightIntensity = 1.0f / ((a * distanceToLight + b) * distanceToLight + 1.0f);

    float ambient = 0.15f;
    float diffuse = max(dot(normal, directionToLight), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specular = (diffuse > 0.0f) ? 0.5f * pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    lightingColor = lightColor * (ambient + lightIntensity * (diffuse + specular));
}
