
#version 330 core

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

vec4 directionalLight() {
    float ambientPower = 0.2f;
    vec3 ambient = material.ambient * ambientPower;

    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    vec3 diffuse = material.diffuse * diffusePower;
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec3 specular = material.specular * specularPower;

    return vec4(light.intensity * (ambient + diffuse + specular) * light.color, 1.0f);
}

vec4 pointLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    vec3 ambient = material.ambient * ambientPower;

    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    vec3 diffuse = material.diffuse * diffusePower;

    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec3 specular = material.specular * specularPower;

    return vec4(attenuation * (ambient + diffuse + specular) * light.color, 1.0f);
}

vec4 spotLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    vec3 ambient = material.ambient * ambientPower;

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient
    if (cosTheta < light.cosOuterCutOff) {
        return vec4(attenuation * ambient * light.color, 1.0f);
    }

    float diffusePower = max(dot(normal, directionToLight), 0.0f);

    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;

    // If between the inner cone and the outer cone
    if (cosTheta < light.cosInnerCutOff) {
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }

    vec3 diffuse = material.diffuse * diffusePower;
    vec3 specular = material.specular * specularPower;

    return vec4(attenuation * (ambient + diffuse + specular) * light.color, 1.0f);
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
