
#include "light_caster.h"

namespace skate 
{
    LightCaster::LightCaster(float red, float green, float blue) 
    {
        SetColor(red, green, blue);
    }

    LightCaster::LightCaster(const glm::vec3& color_) 
        : LightCaster(color_.r, color_.g, color_.b) {}
}
