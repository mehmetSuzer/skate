
#include "spot_light.h"

void SpotLight::AssertFOVradian(float FOVradian) const {
    if (FOVradian <= 0.0f || FOVradian > M_PIf) {
        std::string errorMessage = "FOV Must Be Between (0, pi]! Given: " + std::to_string(FOVradian);
        throw Error(errorMessage);
    }
}

void SpotLight::AssertDirection(const glm::vec3& direction) const {
    float length = glm::length(direction);
    if (glm::epsilonNotEqual(length, 1.0f, 1E-6f)) {
        throw Error("Direction Vector Is Not a Unit Vector!");
    }
}

SpotLight::SpotLight(const glm::vec3& position_, float linear_, float quadratic_, 
    const glm::vec3& direction_, float FOVradian, float red, float green, float blue)
    : PointLight(position_, linear_, quadratic_, red, green, blue) {
    SetDirection(direction_);
    SetFOVradian(FOVradian);
}

SpotLight::SpotLight(const glm::vec3& position_, float linear_, float quadratic_, 
    const glm::vec3& direction_, float FOVradian, const glm::vec3& color_)
    : SpotLight(position_, linear_, quadratic_, direction_, FOVradian, color_.r, color_.g, color_.b) {}

SpotLight::SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, 
    const glm::vec3& direction_, float FOVradian, float red, float green, float blue) 
    : PointLight(position_, dist1, atten1, dist2, atten2, red, green, blue) {
    SetDirection(direction_);
    SetFOVradian(FOVradian);
}
    
SpotLight::SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, 
    const glm::vec3& direction_, float FOVradian, const glm::vec3& color_)
    : SpotLight(position_, dist1, atten1, dist2, atten2, direction_, FOVradian, color_.r, color_.g, color_.b) {}
