
#include "directional_light.h"

void DirectionalLight::AssertDirection(const glm::vec3& direction) const {
    float length = glm::length(direction);
    if (glm::epsilonNotEqual(length, 1.0f, 1E-6f)) {
        throw Error("Direction Vector Is Not a Unit Vector!");
    }
}
    
void DirectionalLight::AssertIntensity(float intensity) const {
    if (intensity <= 0.0f || intensity > 1.0f) {
        throw Error("Intensity Must Be In (0,1]!");
    }
}

DirectionalLight::DirectionalLight(const glm::vec3& direction_, float red, float green, float blue, float intensity_) 
    : Light(red, green, blue) {
    SetDirection(direction_);
    SetIntensity(intensity_);
}

DirectionalLight::DirectionalLight(const glm::vec3& direction_, const glm::vec3& color_, float intensity_)
    : DirectionalLight(direction_, color_.r, color_.g, color_.b, intensity_) {}
    
LightInfo DirectionalLight::Shine(const glm::vec3& point) const {
    return LightInfo{
        -direction,
        INFINITY,
        GetIntensity(INFINITY),
    };
}
