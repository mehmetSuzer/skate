
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <assert.h>
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

namespace skate
{
    // For calculations related to position, rotation, and scalar
    class Transform
    {
    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scalar;

        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;

        glm::mat4 modelMatrix;
        glm::mat3 normalMatrix;

        void UpdateVectors(void) noexcept;
        void UpdateModelMatrix(void) noexcept;
        void UpdateModelAndNormalMatrices(void) noexcept;

    public:
        static const glm::vec3 WorldForward;
        static const glm::vec3 WorldBackward;
        static const glm::vec3 WorldRight;
        static const glm::vec3 WorldLeft;
        static const glm::vec3 WorldUp;
        static const glm::vec3 WorldDown;

        Transform(const glm::vec3& position_ = glm::vec3(0.0f), const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 
            const glm::vec3& scalar_ = glm::vec3(1.0f));
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

        inline const glm::vec3& GetForward(void) const noexcept
        {
            return forward;
        }

        inline const glm::vec3& GetRight(void) const noexcept
        {
            return right;
        }

        inline const glm::vec3& GetUp(void) const noexcept
        {
            return up;
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
        void Translate(const glm::vec3& translation) noexcept;

        void SetRotation(const glm::quat& quaternion) noexcept;
        void SetRotation(const glm::vec3& eulerAngles) noexcept;
        // axis must be normalized
        void Rotate(float radian, const glm::vec3& axis);
        void Rotate(const glm::vec3& eulerAngles) noexcept;
        void Rotate(const glm::quat& quaternion) noexcept;

        // scalar_ cannot be negative
        void SetScalar(const glm::vec3& scalar_);
        // scale cannot be negative
        void SetScalar(float scale);
        // scalar_ cannot be negative
        void Scale(const glm::vec3& scalar_);
        // scale cannot be negative
        void Scale(float scale);
    };
}

#endif // __TRANSFORM_H__
