
#ifndef __MODEL_H__
#define __MODEL_H__

#include "light.h"
#include "color_mesh.h"
#include "material_mesh.h"
#include "texture_mesh.h"

namespace skate 
{
    template<typename Mesh>
    class Model 
    {
    private:
        const std::vector<Mesh>& meshes;
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scalar;

        glm::mat4 model;
        glm::mat4 normalMatrix;

    public:
        Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_) noexcept;

        void UpdateModelMatrix(void) noexcept;
        void UpdateModelAndNormalMatrices(void) noexcept;
        void UpdatePosition(const glm::vec3& position_) noexcept;
        void UpdateRotation(const glm::quat& rotation_) noexcept;
        void UpdateScalar(const glm::vec3& scalar_) noexcept;

        void Draw(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#include "model.cpp"

#endif // __MODEL_H__
