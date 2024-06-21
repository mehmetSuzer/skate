
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
    glm::vec3 color;
    bool active;

    void AssertColorValidity(float red, float green, float blue) const;

public:
    Light(float red, float green, float blue);
    Light(const glm::vec3& color_);

    const glm::vec3& GetColor(void) const {
        return color;
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

    virtual float GetIntensity(float distance) const = 0;

    // Returns .distance = NAN if the point cannot get light from the light source
    virtual LightInfo Shine(const glm::vec3& point) const = 0;
};

#endif // __LIGHT_H__
