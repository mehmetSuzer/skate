
#ifndef __LIGHT_CASTER_H__
#define __LIGHT_CASTER_H__

#include "exception.h"
#include "glm.hpp"

namespace color {
    const glm::vec3 red =       glm::vec3(1.0f,  0.0f,  0.0f);
    const glm::vec3 green =     glm::vec3(0.0f,  1.0f,  0.0f);
    const glm::vec3 blue =      glm::vec3(0.0f,  0.0f,  1.0f);
    const glm::vec3 yellow =    glm::vec3(1.0f,  1.0f,  0.0f);
    const glm::vec3 magenta =   glm::vec3(1.0f,  0.0f,  1.0f);
    const glm::vec3 cyan =      glm::vec3(0.0f,  1.0f,  1.0f);

    const glm::vec3 black =     glm::vec3(0.0f,  0.0f,  0.0f);
    const glm::vec3 darkGray =  glm::vec3(0.25f, 0.25f, 0.25f);
    const glm::vec3 gray =      glm::vec3(0.5f,  0.5f,  0.5f);
    const glm::vec3 lightGray = glm::vec3(0.75f, 0.75f, 0.75f);
    const glm::vec3 white =     glm::vec3(1.0f,  1.0f,  1.0f);
}

enum LightCasterType {
    DIRECTIONAL_LIGHT = 0,
    POINT_LIGHT,
    SPOT_LIGHT,
};

typedef struct {
    enum LightCasterType type;
    glm::vec3 color;        // all
    glm::vec3 position;     // point and spot
    glm::vec3 direction;    // directional and spot
    float intensity;        // directional
    float linear;           // point and spot
    float quadratic;        // point and spot
    float cosInnerCutOff;   // spot
    float cosOuterCutOff;   // spot
 } Light;

class LightCaster {
private:
    glm::vec3 color;
    bool active = true;;

    void AssertColorValidity(float red, float green, float blue) const;

public:
    LightCaster(float red, float green, float blue);
    LightCaster(const glm::vec3& color_);

    virtual ~LightCaster() {}

    const glm::vec3& GetColor(void) const {
        return (active) ? color : color::black;
    }

    void SetColor(float red, float green, float blue) {
        AssertColorValidity(red, green, blue);
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

    void Toggle(void) {
        active = !active;
    }

    virtual Light GetLight(void) const = 0;
};

#endif // __LIGHT_CASTER_H__
