
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

LightInfo SpotLight::Shine(const glm::vec3& point) const {
    const glm::vec3 positionToPoint = point - position;
    const float distance = glm::length(positionToPoint);
    const glm::vec3 directionToPoint = positionToPoint / distance;
    const float intensity = GetIntensity(distance);

    if (glm::dot(directionToPoint, direction) <= cosHalfFOVradian) {
        return LightInfo{ .distance = NAN };
    }

    return LightInfo{
        -directionToPoint,
        distance,
        intensity,
    };
}
