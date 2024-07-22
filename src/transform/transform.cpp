
#include "transform.h"

namespace skate
{                
    Transform::Transform(const glm::vec3& position_, const glm::quat& quaternion, const glm::vec3& scalar_)
        : position(position_), rotation(quaternion), scalar(scalar_)
    {
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
        
    void Transform::SetRotation(const glm::quat& quaternion) noexcept
    {
        rotation = quaternion;
        UpdateModelAndNormalMatrices();
    }

    void Transform::SetRotation(const glm::vec3& eulerAngles) noexcept
    {
        rotation = glm::quat(eulerAngles);
        UpdateModelAndNormalMatrices();
    }
        
    void Transform::SetScalar(const glm::vec3& scalar_) noexcept
    {
        scalar = scalar_;
        UpdateModelAndNormalMatrices();
    }
        
    void Transform::SetScalar(float scale) noexcept
    {
        scalar = glm::vec3(scale);
        UpdateModelAndNormalMatrices();
    }

    void Transform::UpdatePosition(const glm::vec3& deltaPosition) noexcept
    {
        position += deltaPosition;
        UpdateModelMatrix();
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
