
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
    
LightInfo DirectionalLight::Shine(const glm::vec3& point) const {
    return LightInfo{
        -direction,
        INFINITY,
        GetIntensity(INFINITY),
    };
}
