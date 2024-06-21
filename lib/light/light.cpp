
#include "light.h"

void Light::AssertColorValidity(float red, float green, float blue, float alpha) const {
    if (red < 0.0f || red > 1.0f || green < 0.0f || green > 1.0f || blue < 0.0f || blue > 1.0f || alpha < 0.0f || alpha > 1.0f) {
        std::string errorMessage = "Invalid RGBA Values! Given: " + 
            std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue) + " " + std::to_string(alpha);
        throw Error(errorMessage);
    }
}

Light::Light(float red, float green, float blue, float alpha) {
    SetColor(red, green, blue, alpha);
    Activate();
}

Light::Light(const glm::vec4& color_) : Light(color_.r, color_.g, color_.b, color_.a) {}
