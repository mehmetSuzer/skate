
#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "light_caster.h"

namespace skate 
{
    class PointLight : public LightCaster 
    {
    private:
        void AssertAttenuationCoefficients(float linear_, float quadratic_) const;

    protected:
        glm::vec3 position;
        float linear;
        float quadratic;

    public:
        PointLight(const glm::vec3& position_, float linear_, float quadratic_, float red, float green, float blue);
        PointLight(const glm::vec3& position_, float linear_ = 0.14f, float quadratic_ = 0.07f, const glm::vec3& color_ = glm::vec3(1.0f, 1.0f ,1.0f));

        PointLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, float red, float green, float blue);
        PointLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& color_ = glm::vec3(1.0f, 1.0f, 1.0f));

        inline void SetPosition(const glm::vec3& position_) noexcept 
        {
            position = position_;
        }

        inline void SetAttenuationCoefficients(float linear_, float quadratic_) 
        {
            AssertAttenuationCoefficients(linear_, quadratic_);
            linear = linear_;
            quadratic = quadratic_;
        }

        inline Light GetLight(void) const noexcept override 
        {
            return Light 
            {
                .type = POINT_LIGHT,
                .color = GetColor(),
                .position = position,
                .linear = linear,
                .quadratic = quadratic,
            };
        }
    };
}

#endif // __POINT_LIGHT_H__
