
#ifndef __LIGHT_CASTER_H__
#define __LIGHT_CASTER_H__

#include <assert.h>
#include "glm.hpp"

namespace skate 
{
    // Common colors
    namespace color 
    {
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

    enum LightCasterType 
    {
        DIRECTIONAL_LIGHT = 0,
        POINT_LIGHT,
        SPOT_LIGHT,
    };

    typedef struct 
    {
        const enum LightCasterType type;
        const glm::vec3 color;        // all
        const glm::vec3 position;     // point and spot
        const glm::vec3 direction;    // directional and spot
        const float intensity;        // directional
        const float linear;           // point and spot
        const float quadratic;        // point and spot
        const float cosInnerCutOff;   // spot
        const float cosOuterCutOff;   // spot
    } Light;

    // Abstract class for light sources
    class LightCaster 
    {
    private:
        glm::vec3 color;
        bool active = true;

    public:
        LightCaster(float red, float green, float blue);
        LightCaster(const glm::vec3& color_ = glm::vec3(1.0f));

        virtual ~LightCaster() {}

        inline const glm::vec3& GetColor(void) const noexcept 
        {
            return (active) ? color : color::black;
        }

        inline void SetColor(float red, float green, float blue) 
        {
            assert(0.0f <= red && red <= 1.0f && 0.0f <= green && green <= 1.0f && 0.0f <= blue && blue <= 1.0f);
            color = glm::vec3(red, green, blue);
        }

        inline void SetColor(const glm::vec3& color_) 
        {
            SetColor(color_.r, color_.g, color_.b);
        }

        inline bool IsActive(void) const noexcept 
        {
            return active;
        }

        inline void Activate(void) noexcept 
        {
            active = true;
        }

        inline void Deactivate(void) noexcept 
        {
            active = false;
        }

        inline void Toggle(void) noexcept 
        {
            active = !active;
        }

        inline virtual Light GetLight(void) const noexcept = 0;
    };
}

#endif // __LIGHT_CASTER_H__
