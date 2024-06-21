
#include "point_light.h"

void PointLight::AssertIntensityCoefficients(float a_, float b_) const {
    if (a_ < 0.0f || b_ < 0.0f) {
        std::string errorMessage = "Intensity Coefficients Cannot Be Negative. Given: " + std::to_string(a_) + " " + std::to_string(b_);
        throw Error(errorMessage);
    }
}

PointLight::PointLight(const glm::vec3& position_, float red, float green, float blue, float alpha, float a_, float b_)
    : Light(red, green, blue, alpha), position(position_)  {
    SetIntensityCoefficients(a_, b_);
}

PointLight::PointLight(const glm::vec3& position_, const glm::vec4& color_, float a_, float b_)
    : PointLight(position_, color_.r, color_.g, color_.b, color_.a, a_, b_) {}

LightInfo PointLight::Shine(const glm::vec3& point) const {
    glm::vec3 pointToPosition = position - point;
    float distance = glm::length(pointToPosition);

    return LightInfo{
        pointToPosition / distance,
        distance,
        GetIntensity(distance),
    };
}
