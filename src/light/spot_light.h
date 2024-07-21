
#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "point_light.h"
#include "gtc/epsilon.hpp"

namespace skate 
{
    class SpotLight : public PointLight 
    {
    private:
        glm::vec3 direction;
        float cosInnerCutOff;
        float cosOuterCutOff;

        void AssertCutOffRadian(float cutOffRadian) const;
        void AssertInnerLessThanOuter(float innerCutOffRadian, float outerCutOffRadian) const;
        void AssertDirection(const glm::vec3& direction) const;

    public:
        SpotLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& direction_, 
            float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue);
        SpotLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& direction_, 
            float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_);

        SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& direction_, 
            float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue);
        SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& direction_, 
            float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_);

        inline void SetDirection(const glm::vec3& direction_) 
        {
            AssertDirection(direction_);
            direction = direction_;
        }

        inline void SetCutOffRadians(float innerCutOffRadian, float outerCutOffRadian) 
        {
            AssertCutOffRadian(innerCutOffRadian);
            AssertCutOffRadian(outerCutOffRadian);
            AssertInnerLessThanOuter(innerCutOffRadian, outerCutOffRadian);
            cosInnerCutOff = glm::cos(innerCutOffRadian);
            cosOuterCutOff = glm::cos(outerCutOffRadian);
        }

        inline Light GetLight(void) const noexcept override 
        {
            return Light 
            {
                .type = SPOT_LIGHT,
                .color = GetColor(),
                .position = position,
                .direction = direction,
                .linear = linear,
                .quadratic = quadratic,
                .cosInnerCutOff = cosInnerCutOff,
                .cosOuterCutOff = cosOuterCutOff,
            };
        }
    };
}

#endif // __SPOT_LIGHT_H__
