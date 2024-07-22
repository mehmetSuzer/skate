
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

namespace skate
{
    class Transform
    {
    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scalar;

        glm::mat4 modelMatrix;
        glm::mat3 normalMatrix;

        void UpdateModelMatrix(void) noexcept;
        void UpdateModelAndNormalMatrices(void) noexcept;

    public:
        Transform(const glm::vec3& position_, const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scalar_ = glm::vec3(1.0f));
        Transform(const glm::vec3& position_, const glm::quat& quaternion, float scale);
        Transform(const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_);
        Transform(const glm::vec3& position_, const glm::vec3& eulerAngles, float scale);
        
        inline const glm::vec3& GetPosition(void) const noexcept
        {
            return position;
        }

        inline const glm::quat& GetRotation(void) const noexcept
        {
            return rotation;
        }

        inline const glm::vec3& GetScalar(void) const noexcept
        {
            return scalar;
        }

        inline const glm::mat4& GetModelMatrix(void) const noexcept
        {
            return modelMatrix;
        }

        inline const glm::mat3& GetNormalMatrix(void) const noexcept
        {
            return normalMatrix;
        }

        void SetPosition(const glm::vec3& position_) noexcept;
        void SetRotation(const glm::quat& quaternion) noexcept;
        void SetRotation(const glm::vec3& eulerAngles) noexcept;
        void SetScalar(const glm::vec3& scalar_) noexcept;
        void SetScalar(float scale) noexcept;

        void UpdatePosition(const glm::vec3& deltaPosition) noexcept;
    };
}

#endif // __TRANSFORM_H__
