
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;

#define MAX_LIGHT_CASTER_NUMBER 8

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
uniform int lightCasterNumber;
uniform Light lights[MAX_LIGHT_CASTER_NUMBER];

vec3 position;
vec3 normal;

vec4 directionalLight(Light light) {
    float ambientPower = 0.1f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    return light.intensity * (ambientPower + diffusePower + specularPower) * aColor * vec4(light.color, 1.0f);
}

vec4 pointLight(Light light) {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    return attenuation * (ambientPower + diffusePower + specularPower) * aColor * vec4(light.color, 1.0f);
}

vec4 spotLight(Light light) {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient
    if (cosTheta < light.cosOuterCutOff) {
        return attenuation * ambientPower * aColor * vec4(light.color, 1.0f);
    }

    float diffusePower = max(dot(normal, directionToLight), 0.0f);

    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;

    // If between the inner cone and the outer cone
    if (cosTheta < light.cosInnerCutOff) {
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }

    return attenuation * (ambientPower + diffusePower + specularPower) * aColor * vec4(light.color, 1.0f);
}

void main() {
    position = vec3(model * vec4(aPosition, 1.0f));
    gl_Position = projectionView * vec4(position, 1.0f);
    normal = normalize(normalMatrix * aNormal);
    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < lightCasterNumber; i++) {
        if (lights[i].type == DIRECTIONAL_LIGHT) {
            color += directionalLight(lights[i]);
        } else if (lights[i].type == POINT_LIGHT) {
            color += pointLight(lights[i]);
        } else if (lights[i].type == SPOT_LIGHT) {
            color += spotLight(lights[i]);
        }
    }
}
