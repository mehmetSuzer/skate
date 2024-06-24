
#include "light_caster.h"

void LightCaster::AssertColorValidity(float red, float green, float blue) const {
    if (red < 0.0f || red > 1.0f || green < 0.0f || green > 1.0f || blue < 0.0f || blue > 1.0f) {
        const std::string errorMessage = "Invalid RGB Values! Given: " + 
            std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
        throw Error(errorMessage);
    }
}

LightCaster::LightCaster(float red, float green, float blue) {
    SetColor(red, green, blue);
    Activate();
}

LightCaster::LightCaster(const glm::vec3& color_) 
    : LightCaster(color_.r, color_.g, color_.b) {}
