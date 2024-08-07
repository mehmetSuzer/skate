
#ifndef __LIGHT_CASTER_H__
#define __LIGHT_CASTER_H__

#include <assert.h>
#include "transform.h"

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

    // Abstract class for light sources
    class LightCaster 
    {
    private:
        glm::vec3 color;
        bool active = true;

    public:
        enum LightCasterType 
        {
            DIRECTIONAL_LIGHT = 0,
            POINT_LIGHT,
            SPOT_LIGHT,
        };

        typedef struct 
        {
            const LightCasterType type;
            const glm::vec3 color;        // all
            const glm::vec3 position;     // point and spot
            const glm::vec3 direction;    // directional and spot
            const float intensity;        // directional
            const float linear;           // point and spot
            const float quadratic;        // point and spot
            const float cosInnerCutOff;   // spot
            const float cosOuterCutOff;   // spot
        } Light;
    
        Transform transform;

        virtual ~LightCaster() {}
        
        LightCaster(const glm::vec3& color_)
        {
            SetColor(color_);
        }

        inline const glm::vec3& GetColor(void) const noexcept 
        {
            return (active) ? color : color::black;
        }

        inline void SetColor(const glm::vec3& color_) 
        {
            assert(
                0.0f <= color_.r && color_.r <= 1.0f && 
                0.0f <= color_.g && color_.g <= 1.0f && 
                0.0f <= color_.b && color_.b <= 1.0f
            );
            color = color_;
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
