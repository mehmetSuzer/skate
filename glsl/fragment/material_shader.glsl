
#version 330 core

#include <common/fragment.glsl>
#include <common/material.glsl>

vec4 DirectionalLight(Light light, vec3 directionToCamera)
{
    float ambientPower = 0.2f;
    vec3 ambient = material.ambient * ambientPower;

    float diffusePower = max(dot(fsIn.normal, -light.direction), 0.0f);
    vec3 diffuse = material.diffuse * diffusePower;
    
    vec3 reflectionDirection = reflect(light.direction, fsIn.normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec3 specular = material.specular * specularPower;

    return vec4(light.intensity * (ambient + diffuse + specular) * light.color, 1.0f);
}

vec4 PointLight(Light light, vec3 directionToCamera)
{
    vec3 positionToLightPosition = light.position - fsIn.position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;
    vec3 ambient = material.ambient * ambientPower;

    float diffusePower = max(dot(fsIn.normal, directionToLight), 0.0f);
    vec3 diffuse = material.diffuse * diffusePower;

    vec3 reflectionDirection = reflect(-directionToLight, fsIn.normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;
    vec3 specular = material.specular * specularPower;

    return vec4(attenuation * (ambient + diffuse + specular) * light.color, 1.0f);
}

vec4 SpotLight(Light light, vec3 directionToCamera)
{
    vec3 positionToLightPosition = light.position - fsIn.position;
    float distanceToLight = length(positionToLightPosition);
    vec3 directionToLight = positionToLightPosition / distanceToLight;

    float attenuation = 1.0f / ((light.quadratic * distanceToLight + light.linear) * distanceToLight + 1.0f);

    float ambientPower = 0.1f;
    vec3 ambient = material.ambient * ambientPower;

    float cosTheta = dot(-directionToLight, light.direction);

    // If out of the outer cone, use only ambient
    if (cosTheta < light.cosOuterCutOff)
        return vec4(attenuation * ambient * light.color, 1.0f);

    float diffusePower = max(dot(fsIn.normal, directionToLight), 0.0f);

    vec3 reflectionDirection = reflect(-directionToLight, fsIn.normal);
    float specularPower = (diffusePower > 0.0f) ? pow(max(dot(directionToCamera, reflectionDirection), 0.0f), material.shininess) : 0.0f;

    // If between the inner cone and the outer cone
    if (cosTheta < light.cosInnerCutOff) 
    {
        float epsilon = light.cosInnerCutOff - light.cosOuterCutOff;
        float intensity = clamp((cosTheta - light.cosOuterCutOff) / epsilon, 0.0f, 1.0f);
        diffusePower *= intensity;
        specularPower *= intensity;
    }

    vec3 diffuse = material.diffuse * diffusePower;
    vec3 specular = material.specular * specularPower;

    return vec4(attenuation * (ambient + diffuse + specular) * light.color, 1.0f);
}

void main() 
{
    vec3 directionToCamera = normalize(cameraPosition - fsIn.position);
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
