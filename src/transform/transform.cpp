
#include "transform.h"

namespace skate
{                
    const glm::vec3 Transform::WorldForward  = glm::vec3( 0.0f,  0.0f, -1.0f);
    const glm::vec3 Transform::WorldBackward = glm::vec3( 0.0f,  0.0f,  1.0f);
    const glm::vec3 Transform::WorldRight    = glm::vec3( 1.0f,  0.0f,  0.0f);
    const glm::vec3 Transform::WorldLeft     = glm::vec3(-1.0f,  0.0f,  0.0f);
    const glm::vec3 Transform::WorldUp       = glm::vec3( 0.0f,  1.0f,  0.0f);
    const glm::vec3 Transform::WorldDown     = glm::vec3( 0.0f, -1.0f,  0.0f);

    Transform::Transform(const glm::vec3& position_, const glm::quat& quaternion, const glm::vec3& scalar_)
        : position(position_), rotation(quaternion), scalar(scalar_)
    {
        assert(scalar.x >= 0.0f && scalar.y >= 0.0f && scalar.z >= 0.0f);
        UpdateVectors();
        UpdateModelAndNormalMatrices();
    }

    Transform::Transform(const glm::vec3& position_, const glm::quat& quaternion, float scale)
        : Transform(position_, quaternion, glm::vec3(scale)) {}

    Transform::Transform(const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_)
        : Transform(position_, glm::quat(eulerAngles), scalar_) {}
        
    Transform::Transform(const glm::vec3& position_, const glm::vec3& eulerAngles, float scale)
        : Transform(position_, glm::quat(eulerAngles), scale) {}

    void Transform::SetPosition(const glm::vec3& position_) noexcept
    {
        position = position_;
        UpdateModelMatrix();
    }

    void Transform::Translate(const glm::vec3& translation) noexcept
    {
        position += translation;
        UpdateModelMatrix();
    }
        
    void Transform::SetRotation(const glm::quat& quaternion) noexcept
    {
        rotation = quaternion;
        UpdateVectors();
        UpdateModelAndNormalMatrices();
    }

    void Transform::SetRotation(const glm::vec3& eulerAngles) noexcept
    {
        SetRotation(glm::quat(eulerAngles));
    }

    void Transform::SetForward(const glm::vec3& forward_) noexcept
    {
        glm::highp_bvec3 equal = glm::epsilonEqual(forward, forward_, 1E-6f);
        if (equal.x && equal.y && equal.z)
            return;

        glm::highp_bvec3 opposite = glm::epsilonEqual(forward, -forward_, 1E-6f);
        if (opposite.x && opposite.y && opposite.z)
        {
            Rotate(M_PIf, up);
            return;
        }

        const glm::vec3 axis = glm::normalize(glm::cross(forward, forward_)); 
        const float angle = glm::acos(glm::dot(forward, forward_));
        
        const float cosHalfAngle = glm::cos(angle/2.0f);
        const float sinHalfAngle = glm::sin(angle/2.0f);

        const glm::quat quaternion = glm::quat(cosHalfAngle, sinHalfAngle * axis);
        Rotate(quaternion);
    }

    void Transform::Rotate(float radian, const glm::vec3& axis)
    {
        assert(glm::epsilonEqual(glm::length(axis), 1.0f, 1E-6f));
        rotation = glm::angleAxis(radian, axis) * rotation;
        UpdateVectors();
        UpdateModelAndNormalMatrices();
    }

    void Transform::Rotate(const glm::vec3& eulerAngles) noexcept
    {
        rotation = glm::quat(eulerAngles) * rotation;
        UpdateVectors();
        UpdateModelAndNormalMatrices();
    }

    void Transform::Rotate(const glm::quat& quaternion) noexcept
    {
        rotation = quaternion * rotation;
        UpdateVectors();
        UpdateModelAndNormalMatrices();
    }
        
    void Transform::SetScalar(const glm::vec3& scalar_)
    {
        assert(scalar_.x >= 0.0f && scalar_.y >= 0.0f && scalar_.z >= 0.0f);
        scalar = scalar_;
        UpdateModelAndNormalMatrices();
    }
        
    void Transform::SetScalar(float scale)
    {
        SetScalar(glm::vec3(scale));
    }

    void Transform::Scale(const glm::vec3& scalar_)
    {
        assert(scalar_.x >= 0.0f && scalar_.y >= 0.0f && scalar_.z >= 0.0f);
        scalar *= scalar_;
        UpdateModelAndNormalMatrices();
    }
        
    void Transform::Scale(float scale)
    {
        assert(scale >= 0.0f);
        scalar *= scale;
        UpdateModelAndNormalMatrices();
    }

    void Transform::UpdateVectors(void) noexcept
    {
        forward = glm::normalize(rotation * WorldForward);
        right = glm::normalize(rotation * WorldRight);
        up = glm::normalize(rotation * WorldUp);
    }

    void Transform::UpdateModelMatrix(void) noexcept
    {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = modelMatrix * glm::mat4_cast(rotation);
        modelMatrix = glm::scale(modelMatrix, scalar);
    }
    
    void Transform::UpdateModelAndNormalMatrices(void) noexcept
    {
        const glm::mat3 rotation3x3 = glm::mat3_cast(rotation);
        const glm::mat4 rotation4x4 = glm::mat4(rotation3x3);
        const glm::mat3 inverseScalar3x3 = glm::mat3(1.0f/scalar.x, 0.0f, 0.0f, 0.0f, 1.0f/scalar.y, 0.0f, 0.0f, 0.0f, 1.0f/scalar.z);

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = modelMatrix * rotation4x4;
        modelMatrix = glm::scale(modelMatrix, scalar);

        // normalMatrix = the upper left 3x3 matrix of the transpose of the inverse of the model matrix
        // the following calculation is the mathematically simplified version
        normalMatrix = rotation3x3 * inverseScalar3x3;
    }
}
