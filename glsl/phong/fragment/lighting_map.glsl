
#version 330 core

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

struct MaterialMap {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
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
uniform Light light;
uniform MaterialMap materialMap;

void directionalLight() {
    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    vec4 ambientAndDiffuse = (ambientPower + diffusePower) + texture(materialMap.diffuse, tex);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-light.direction, normal);
    
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;
    vec4 specular = specularPower * vec4(texture(materialMap.specular, tex).rrr, 1.0f);

    float emissionPower = 1.0f;
    vec4 emission = emissionPower * texture(materialMap.emission, tex);

    FragColor = emission + vec4(light.intensity * light.color, 1.0f) * (ambientAndDiffuse + specular);
}

void pointLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    vec4 ambientAndDiffuse = (ambientPower + diffusePower) * texture(materialMap.diffuse, tex);
    
    vec3 directionToCamera = normalize(cameraPosition - position);
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), 16) : 0.0f;
    vec4 specular = specularPower * vec4(texture(materialMap.specular, tex).rrr, 1.0f);

    float emissionPower = 1.0f;
    vec4 emission = emissionPower * texture(materialMap.emission, tex);
    
    FragColor = emission + vec4(attenuation * light.color, 1.0f) * (ambientAndDiffuse + specular);
}

void spotLight() {
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;
    vec3 reflectionDirection = reflect(-directionToLight, normal);

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.2f;
    vec4 ambient = ambientPower * texture(materialMap.diffuse, tex);

    float emissionPower = 1.0f;
    vec4 emission = emissionPower * texture(materialMap.emission, tex);

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient and emission
    if (cosTheta < light.cosOuterCutOff) {
        FragColor = emission + vec4(attenuation * light.color, 1.0f) * ambient;
        return;
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

    vec4 diffuse = diffusePower * texture(materialMap.diffuse, tex);
    vec4 specular = specularPower * vec4(texture(materialMap.specular, tex).rrr, 1.0f);

    FragColor = emission + vec4(attenuation * light.color, 1.0f) * (ambient + diffuse + specular);
}

void main() {
    if (light.type == DIRECTIONAL_LIGHT) {
        directionalLight();
    } else if (light.type == POINT_LIGHT) {
        pointLight();
    } else if (light.type == SPOT_LIGHT) {
        spotLight();
    } else {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}
