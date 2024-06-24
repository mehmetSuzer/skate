
#ifndef __LIGHT_CASTER_H__
#define __LIGHT_CASTER_H__

#include <error.h>
#include <glm.hpp>

enum LightCasterType {
    DIRECTIONAL_LIGHT = 0,
    POINT_LIGHT,
    SPOT_LIGHT,
};

typedef struct {
    enum LightCasterType type;
    glm::vec3 color;            // all
    glm::vec3 position;         // point and spot
    glm::vec3 direction;        // directional and spot
    float intensity;            // directional
    float linear;               // point and spot
    float quadratic;            // point and spot
    float cosInnerCutOffRadian; // spot
    float cosOuterCutOffRadian; // spot
 } Light;

class LightCaster {
private:
    glm::vec3 color;
    bool active;

    void AssertColorValidity(float red, float green, float blue) const;

public:
    LightCaster(float red, float green, float blue);
    LightCaster(const glm::vec3& color_);

    virtual ~LightCaster() {}

    const glm::vec3& GetColor(void) const {
        return color;
    }

    void SetColor(float red, float green, float blue) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertColorValidity(red, green, blue);
    #endif
        color = glm::vec3(red, green, blue);
    }

    void SetColor(const glm::vec3& color_) {
        SetColor(color_.r, color_.g, color_.b);
    }

    bool IsActive(void) const {
        return active;
    }

    void Activate(void) {
        active = true;
    }

    void Deactivate(void) {
        active = false;
    }

    virtual Light GetLight(void) const = 0;
};

#endif // __LIGHT_CASTER_H__
