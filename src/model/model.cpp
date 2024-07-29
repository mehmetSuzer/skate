
#include "model.h"

namespace skate 
{
    template<typename Mesh>
    Model<Mesh>::Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& quaternion, const glm::vec3& scalar_) noexcept
        : transform(Transform(position_, quaternion, scalar_)), meshes(meshes_) {}
    
    template<typename Mesh>
    Model<Mesh>::Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& quaternion, float scale) noexcept
        : transform(Transform(position_, quaternion, scale)), meshes(meshes_) {}
    
    template<typename Mesh>
    Model<Mesh>::Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_) noexcept
        : transform(Transform(position_, eulerAngles, scalar_)), meshes(meshes_) {}
    
    template<typename Mesh>
    Model<Mesh>::Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::vec3& eulerAngles, float scale) noexcept
        : transform(Transform(position_, eulerAngles, scale)), meshes(meshes_) {}

    template<typename Mesh>
    void Model<Mesh>::Draw(const Shader& shader) const noexcept 
    {
        shader.Use();
        shader.SetUniformMat4(transform.GetModelMatrix(), "model");
        shader.SetUniformMat3(transform.GetNormalMatrix(), "normalMatrix");

        for (uint32_t i = 0; i < meshes.size(); i++) 
            meshes[i].Draw(shader);
    }

    template<typename Mesh>
    void Model<Mesh>::DrawBorder(const Shader& shader) const noexcept
    {
        if (selected)
            Draw(shader);
    }

    template<typename Mesh>
    void Model<Mesh>::Delete(void) const noexcept 
    {
        for (uint32_t i = 0; i < meshes.size(); i++) 
            meshes[i].Delete();
    }
}
