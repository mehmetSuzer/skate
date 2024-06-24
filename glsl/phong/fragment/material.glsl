
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

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

out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

vec4 directionalLight() {
    float ambientPower = 1.0f;
    vec4 ambient = vec4(material.ambient, 1.0f) * ambientPower;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    vec4 diffuse = vec4(material.diffuse, 1.0f) * diffusePower;
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec4 specular = vec4(material.specular, 1.0f) * specularPower;

    return vec4(light.color, 1.0f) * light.intensity * (ambient + diffuse + specular);
}

vec4 pointLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 1.0f;
    vec4 ambient = vec4(material.ambient, 1.0f) * ambientPower;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    vec4 diffuse = vec4(material.diffuse, 1.0f) * diffusePower;
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec4 specular = vec4(material.specular, 1.0f) * specularPower;

    return vec4(light.color, 1.0f) * attenuation * (ambient + diffuse + specular);
}

vec4 spotLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 1.0f;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;

    float cosTheta = dot(-directionToLight, light.direction);
    
    if (cosTheta < light.cosOuterCutOff) {
        // Out of the outer cone, use only the ambient light
        diffusePower = 0.0f;
        specularPower = 0.0f;
    } else if (cosTheta < light.cosInnerCutOff) {
        // Between the inner cone and the outer cone
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }
    // else: Inside the inner cone

    vec4 ambient = vec4(material.ambient, 1.0f) * ambientPower;
    vec4 diffuse = vec4(material.diffuse, 1.0f) * diffusePower;
    vec4 specular = vec4(material.specular, 1.0f) * specularPower;

    return vec4(light.color, 1.0f) * attenuation * (ambient + diffuse + specular);
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
