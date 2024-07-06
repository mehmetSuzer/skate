
#version 330 core

#define MAX_LIGHT_CASTER_NUMBER 8

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

struct MaterialMap {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

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

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 tex;

uniform vec3 cameraPosition;
uniform MaterialMap materialMap;
uniform int lightCasterNumber;
uniform Light lights[MAX_LIGHT_CASTER_NUMBER];

vec4 directionalLight(Light light) {
    float ambientPower = 0.1f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), materialMap.shininess) : 0.0f;
    specularPower *= texture(materialMap.specular, tex).r;

    float emissionPower = 1.0f;
    vec4 emission = emissionPower * texture(materialMap.emission, tex);

    return emission + light.intensity * (ambientPower + diffusePower + specularPower) * texture(materialMap.diffuse, tex) * vec4(light.color, 1.0f);
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
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), materialMap.shininess) : 0.0f;
    specularPower *= texture(materialMap.specular, tex).r;

    float emissionPower = 1.0f;
    vec4 emission = emissionPower * texture(materialMap.emission, tex);
    
    return emission + attenuation * (ambientPower + diffusePower + specularPower) * texture(materialMap.diffuse, tex) * vec4(light.color, 1.0f);
}

vec4 spotLight(Light light) {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;

    float emissionPower = 1.0f;
    vec4 emission = emissionPower * texture(materialMap.emission, tex);

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient and emission
    if (cosTheta < light.cosOuterCutOff) {
        return emission + attenuation * ambientPower * texture(materialMap.diffuse, tex) * vec4(light.color, 1.0f);
    }

    vec3 directionToCamera = normalize(cameraPosition - position);
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), materialMap.shininess) : 0.0f;
    specularPower *= texture(materialMap.specular, tex).r;

    // If between the inner cone and the outer cone
    if (cosTheta < light.cosInnerCutOff) {
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }

    return emission + attenuation * (ambientPower + diffusePower + specularPower) * texture(materialMap.diffuse, tex) * vec4(light.color, 1.0f);
}

void main() {
    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < lightCasterNumber; i++) {
        if (lights[i].type == DIRECTIONAL_LIGHT) {
            FragColor += directionalLight(lights[i]);
        } else if (lights[i].type == POINT_LIGHT) {
            FragColor += pointLight(lights[i]);
        } else if (lights[i].type == SPOT_LIGHT) {
            FragColor += spotLight(lights[i]);
        }
    }
}
