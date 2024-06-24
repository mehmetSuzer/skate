
#version 330 core

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

struct Light {
    int type;
    vec3 color;                 // all
    vec3 position;              // point and spot
    vec3 direction;             // directional and spot
    float intensity;            // directional
    float linear;               // point and spot
    float quadratic;            // point and spot
    float cosInnerCutOffRadian; // spot
    float cosOuterCutOffRadian; // spot
};

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 tex;

uniform vec3 cameraPosition;
uniform Light light;
uniform sampler2D textureImage;

vec4 directionalLight() {
    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? 0.5f * pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    return texture(textureImage, tex) * vec4(light.color, 1.0f) * light.intensity * (ambientPower + diffusePower + specularPower);
}

vec4 pointLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? 0.5f * pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    return texture(textureImage, tex) * vec4(light.color, 1.0f) * attenuation * (ambientPower + diffusePower + specularPower);
}

vec4 spotLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? 0.5f * pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    float cosTheta = dot(-directionToLight, light.direction);
    
    if (cosTheta < light.cosOuterCutOffRadian) {
        // Out of the outer cone, use only the ambient light
        diffusePower = 0.0f;
        specularPower = 0.0f;
    } else if (cosTheta < light.cosInnerCutOffRadian) {
        // Between the inner cone and the outer cone
        float epsilon = light.cosInnerCutOffRadian - light.cosOuterCutOffRadian;
        float intensity = clamp((cosTheta - light.cosOuterCutOffRadian) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }
    // else: Inside the inner cone

    return texture(textureImage, tex) * vec4(light.color, 1.0f) * attenuation * (ambientPower + diffusePower + specularPower);
}

void main() {
    if (light.type == DIRECTIONAL_LIGHT) {
        FragColor = directionalLight();
    } else if (light.type == POINT_LIGHT) {
        FragColor = pointLight();
    } else if (light.type == SPOT_LIGHT) {
        FragColor = spotLight();
    } else {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}
