
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec4 color;
    vec3 position;
};

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out vec4 color;

uniform mat4 model;
uniform mat4 projectionView;
uniform mat3 normalMatrix;

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

void main() {
    vec3 position = vec3(model * vec4(aPosition, 1.0f));
    gl_Position = projectionView * vec4(position, 1.0f);
    vec3 normal = normalMatrix * aNormal;

    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float a = 0.2f;
    float b = 0.7f;
    float lightIntensity = 1.0f / ((a * distanceToLight + b) * distanceToLight + 1.0f);

    float ambientPower = 0.5f;
    vec4 ambient = vec4(material.ambient, 1.0f) * ambientPower;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    vec4 diffuse = vec4(material.diffuse, 1.0f) * diffusePower;
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec4 specular = vec4(material.specular, 1.0f) * specularPower;

    color = light.color * (ambient + lightIntensity * (diffuse + specular));
}
