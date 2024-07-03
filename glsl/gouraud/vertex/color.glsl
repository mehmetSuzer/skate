
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

struct Light {
    int type;
    vec3 color;             // all
    vec3 position;          // point and spot
    vec3 direction;         // directional and spot
    float intensity;        // directional
    float linear;           // point and spot
    float quadratic;        // point and spot
    float cosInnerCutOff;   // spot
    float cosOuterCutOff;   // spot
};

out vec4 color;

uniform mat4 model;
uniform mat4 projectionView;
uniform mat3 normalMatrix;

uniform vec3 cameraPosition;
uniform Light light;

vec3 position;
vec3 normal;

vec4 directionalLight() {
    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    return aColor * vec4(light.color, 1.0f) * light.intensity * (ambientPower + diffusePower + specularPower);
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
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    return aColor * vec4(light.color, 1.0f) * attenuation * (ambientPower + diffusePower + specularPower);
}

vec4 spotLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;
    vec3 reflectionDirection = reflect(-directionToLight, normal);

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient
    if (cosTheta < light.cosOuterCutOff) {
        return aColor * vec4(light.color, 1.0f) * attenuation * ambientPower;
    }

    vec3 directionToCamera = normalize(cameraPosition - position);
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    // If between the inner cone and the outer cone
    if (cosTheta < light.cosInnerCutOff) {
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }

    return aColor * vec4(light.color, 1.0f) * attenuation * (ambientPower + diffusePower + specularPower);
}

void main() {
    position = vec3(model * vec4(aPosition, 1.0f));
    gl_Position = projectionView * vec4(position, 1.0f);
    normal = normalMatrix * aNormal;

    if (light.type == DIRECTIONAL_LIGHT) {
        color = directionalLight();
    } else if (light.type == POINT_LIGHT) {
        color = pointLight();
    } else if (light.type == SPOT_LIGHT) {
        color = spotLight();
    } else {
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}
