
#version 330 core

#include <common/light.glsl>
#include <common/color_uniforms.glsl>

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec4 color;

uniform vec3 cameraPosition;

vec4 DirectionalLight(Light light, vec3 directionToCamera)
{
    float ambientPower = 0.2f;
    float diffusePower = max(dot(normal, -light.direction), 0.0f);
    
    vec3 reflectionDirection = reflect(light.direction, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), DEFAULT_SHININESS) : 0.0f;
    specularPower *= metalness;

    return light.intensity * (ambientPower + diffusePower + specularPower) * color * vec4(light.color, 1.0f);
}

vec4 PointLight(Light light, vec3 directionToCamera)
{
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;
    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), DEFAULT_SHININESS) : 0.0f;
    specularPower *= metalness;

    return attenuation * (ambientPower + diffusePower + specularPower) * color * vec4(light.color, 1.0f);
}

vec4 SpotLight(Light light, vec3 directionToCamera)
{
    vec3 positionToLightPosition = light.position - position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient
    if (cosTheta < light.cosOuterCutOff)
        return attenuation * ambientPower * color * vec4(light.color, 1.0f);

    float diffusePower = max(dot(normal, directionToLight), 0.0f);
    
    vec3 reflectionDirection = reflect(-directionToLight, normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), DEFAULT_SHININESS) : 0.0f;
    specularPower *= metalness;

    // If between the inner cone and the outer cone
    if (cosTheta < light.cosInnerCutOff) 
    {
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }

    return attenuation * (ambientPower + diffusePower + specularPower) * color * vec4(light.color, 1.0f);
}

void main() 
{
    vec3 directionToCamera = normalize(cameraPosition - position);
    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < lightCasterNumber; i++) 
    {
        if (lights[i].type == DIRECTIONAL_LIGHT)
            FragColor += DirectionalLight(lights[i], directionToCamera);
        else if (lights[i].type == POINT_LIGHT)
            FragColor += PointLight(lights[i], directionToCamera);
        else if (lights[i].type == SPOT_LIGHT)
            FragColor += SpotLight(lights[i], directionToCamera);
    }
}
