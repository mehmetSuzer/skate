
#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "point_light.h"
#include "gtc/epsilon.hpp"

namespace skate 
{
    // A light source that is located somewhere in the environment that, 
    // instead of shooting light rays in all directions, 
    // only shoots them in a specific direction
    class SpotLight : public PointLight 
    {
    private:
        glm::vec3 direction;
        float cosInnerCutOff;
        float cosOuterCutOff;

    public:
        SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float linear_, float quadratic_,
            float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue);
        SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float linear_ = 0.14f, float quadratic_ = 0.07f,
            float innerCutOffRadian = M_PIf/8.0f, float outerCutOffRadian = M_PIf/6.0f, const glm::vec3& color_ = glm::vec3(1.0f));

        SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float dist1, float atten1, float dist2, float atten2,
            float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue);
        SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float dist1, float atten1, float dist2, float atten2, 
            float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_);

        inline void SetDirection(const glm::vec3& direction_) 
        {
            assert(glm::epsilonEqual(glm::length(direction_), 1.0f, 1E-6f));
            direction = direction_;
        }

        inline void SetCutOffRadians(float innerCutOffRadian, float outerCutOffRadian) 
        {
            assert(0.0f < innerCutOffRadian && innerCutOffRadian < M_PIf);
            assert(0.0f < outerCutOffRadian && outerCutOffRadian < M_PIf);
            assert(innerCutOffRadian < outerCutOffRadian);
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
