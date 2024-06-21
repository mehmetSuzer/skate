
#include "light.h"

void Light::AssertColorValidity(float red, float green, float blue) const {
    if (red < 0.0f || red > 1.0f || green < 0.0f || green > 1.0f || blue < 0.0f || blue > 1.0f) {
        std::string errorMessage = "Invalid Color: " + std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
        throw Error(errorMessage);
    }
}

Light::Light(float red, float green, float blue) {
    SetColor(red, green, blue);
    Activate();
}

Light::Light(const glm::vec3& color_) : Light(color_.r, color_.g, color_.b) {}
