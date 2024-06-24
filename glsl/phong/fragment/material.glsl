
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 color;
    vec3 position;
};
  
out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

void main() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float a = 0.2f;
    float b = 0.7f;
    float attenuation = 1.0f / ((a * distanceToLight + b) * distanceToLight + 1.0f);

    float ambientPower = 1.0f;
    vec4 ambient = vec4(material.ambient, 1.0f) * ambientPower;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    vec4 diffuse = vec4(material.diffuse, 1.0f) * diffusePower;
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec4 specular = vec4(material.specular, 1.0f) * specularPower;

    FragColor = vec4(light.color, 1.0f) * attenuation * (ambient + diffuse + specular);
}
