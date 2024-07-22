
#ifndef __LOADABLE_COLOR_MODEL_H__
#define __LOADABLE_COLOR_MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "color_mesh.h"
#include "gtc/type_ptr.hpp"

namespace skate 
{
    class LoadableColorModel 
    {
    private:
        std::vector<ColorMesh> meshes;

        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scalar;

        glm::mat4 model;
        glm::mat4 normalMatrix;

        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene) noexcept;
        ColorMesh ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept;
        
    public:
        LoadableColorModel(const std::string& path, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_);

        void UpdateModelMatrix(void) noexcept;
        void UpdateModelAndNormalMatrices(void) noexcept;
        void UpdatePosition(const glm::vec3& position_) noexcept;
        void UpdateRotation(const glm::quat& rotation_) noexcept;
        void UpdateScalar(const glm::vec3& scalar_) noexcept;

        void Draw(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#endif // __LOADABLE_COLOR_MODEL_H__
