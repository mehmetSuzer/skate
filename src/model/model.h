
#ifndef __MODEL_H__
#define __MODEL_H__

#include "transform.h"
#include "color_mesh.h"
#include "material_mesh.h"
#include "texture_mesh.h"

namespace skate 
{
    // A model contains a set of meshes of the same type.
    template<typename Mesh>
    class Model 
    {
    private:
        const std::vector<Mesh>& meshes;

    public:
        Transform transform;

        Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, 
            const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scalar_ = glm::vec3(1.0f)) noexcept;
        
        Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& quaternion, float scale) noexcept;
        Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_) noexcept;
        Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::vec3& eulerAngles, float scale) noexcept;

        void Draw(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#include "model.cpp"

#endif // __MODEL_H__
