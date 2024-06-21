
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

SpotLight::SpotLight(const glm::vec3& position_, float red, float green, float blue, float alpha, float a_, float b_, const glm::vec3& direction_, float FOVradian)
    : PointLight(position_, red, green, blue, alpha, a_, b_) {
    SetDirection(direction_);
    SetFOVradian(FOVradian);
}

SpotLight::SpotLight(const glm::vec3& position_, const glm::vec4& color_, float a_, float b_, const glm::vec3& direction_, float FOVradian)
    : SpotLight(position_, color_.r, color_.g, color_.b, color_.a, a_, b_, direction_, FOVradian) {}

LightInfo SpotLight::Shine(const glm::vec3& point) const {
    glm::vec3 positionToPoint = point - position;
    float distance = glm::length(positionToPoint);
    glm::vec3 directionToPoint = positionToPoint / distance;
    float intensity = (glm::dot(directionToPoint, direction) > cosHalfFOVradian) ? GetIntensity(distance) : 0.0f;

    return LightInfo{
        -directionToPoint,
        distance,
        intensity,
    };
}
