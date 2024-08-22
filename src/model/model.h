
#ifndef __MODEL_H__
#define __MODEL_H__

#include "renderable.h"
#include "color_mesh.h"
#include "material_mesh.h"
#include "texture_mesh.h"

namespace skate 
{
    // A model contains a set of meshes of the same type.
    template<typename Mesh>
    class Model : public Renderable
    {
    private:
        std::vector<Mesh> meshes;

    public:
        Model(const glm::vec3& position_, const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 
            const glm::vec3& scalar_ = glm::vec3(1.0f)) noexcept
        {
            transform = Transform(position_, quaternion, scalar_);
        }
        
        Model(const glm::vec3& position_, const glm::quat& quaternion, float scale) noexcept
        {
            transform = Transform(position_, quaternion, scale);
        }
        
        Model(const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_) noexcept
        {
            transform = Transform(position_, eulerAngles, scalar_);
        }
        
        Model(const glm::vec3& position_, const glm::vec3& eulerAngles, float scale) noexcept
        {
            transform = Transform(position_, eulerAngles, scale);
        }
        
        void AddMesh(const Mesh& mesh) noexcept
        {
            meshes.push_back(mesh);
        }

        void Render(const Shader& shader) const noexcept override
        {
            RenderState::Instance().UseShader(shader);
            shader.SetUniformMat4(transform.GetModelMatrix(), "model");
            shader.SetUniformMat3(transform.GetNormalMatrix(), "normalMatrix");

            for (uint32_t i = 0; i < meshes.size(); i++) 
                meshes[i].Draw(shader);
        }
        
        void Delete(void) const noexcept override
        {
            for (uint32_t i = 0; i < meshes.size(); i++) 
                meshes[i].Delete();
        }
    };
}

#endif // __MODEL_H__
