
#include "model.h"

namespace skate 
{
    template<typename Mesh>
    Model<Mesh>::Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_) noexcept
        : meshes(meshes_), position(position_), rotation(rotation_), scalar(scalar_) 
    {
        UpdateModelAndNormalMatrices();
    }

    template<typename Mesh>
    void Model<Mesh>::UpdateModelMatrix(void) noexcept 
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = model * glm::mat4_cast(rotation);
        model = glm::scale(model, scalar);
    }

    template<typename Mesh>
    void Model<Mesh>::UpdateModelAndNormalMatrices(void) noexcept 
    {
        const glm::mat3 rotation3x3 = glm::mat3_cast(rotation);
        const glm::mat4 rotation4x4 = glm::mat4(rotation3x3);
        const glm::mat3 inverseScalar3x3 = glm::mat3(1.0f/scalar.x, 0.0f, 0.0f, 0.0f, 1.0f/scalar.y, 0.0f, 0.0f, 0.0f, 1.0f/scalar.z);

        model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = model * rotation4x4;
        model = glm::scale(model, scalar);

        // normalMatrix = the upper left 3x3 matrix of the transpose of the inverse of the model matrix
        // the following calculation is the mathematically simplified version
        normalMatrix = rotation3x3 * inverseScalar3x3;
    }

    template<typename Mesh>
    void Model<Mesh>::UpdatePosition(const glm::vec3& position_) noexcept 
    {
        position = position_;
        UpdateModelMatrix();
    }

    template<typename Mesh>
    void Model<Mesh>::UpdateRotation(const glm::quat& rotation_) noexcept 
    {
        rotation = rotation_;
        UpdateModelAndNormalMatrices();
    }

    template<typename Mesh>
    void Model<Mesh>::UpdateScalar(const glm::vec3& scalar_) noexcept 
    {
        scalar = scalar_;
        UpdateModelAndNormalMatrices();
    }

    template<typename Mesh>
    void Model<Mesh>::Draw(const Shader& shader) const noexcept 
    {
        shader.Use();
        shader.SetUniformMat4(model, "model");
        shader.SetUniformMat3(normalMatrix, "normalMatrix");

        for (uint32_t i = 0; i < meshes.size(); i++) 
        {
            meshes[i].Draw(shader);
        }
    }

    template<typename Mesh>
    void Model<Mesh>::Delete(void) const noexcept 
    {
        for (uint32_t i = 0; i < meshes.size(); i++) 
        {
            meshes[i].Delete();
        }
    }
}
