
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <error.h>
#include <glm.hpp>

typedef struct {
    glm::vec3 directionToLight;
    float distance;
    float intensity;
} LightInfo;

class Light {
private:
    glm::vec4 color;
    bool active;

    void AssertColorValidity(float red, float green, float blue, float alpha) const;

public:
    Light(float red, float green, float blue, float alpha);
    Light(const glm::vec4& color_);

    const glm::vec4& GetColor(void) const {
        return color;
    }

    void SetColor(float red, float green, float blue, float alpha) {
    #if COMPILE_ERROR_HANDLERS
        AssertColorValidity(red, green, blue, alpha);
    #endif
        color = glm::vec4(red, green, blue, alpha);
    }

    void SetColor(const glm::vec4& color_) {
        SetColor(color_.r, color_.g, color_.b, color_.a);
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

    virtual float GetIntensity(float distance) const = 0;
    virtual LightInfo Shine(const glm::vec3& point) const = 0;
};

#endif // __LIGHT_H__
