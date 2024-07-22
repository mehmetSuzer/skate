
#ifndef __LOADABLE_COLOR_MODEL_H__
#define __LOADABLE_COLOR_MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "transform.h"
#include "color_mesh.h"

namespace skate 
{
    class LoadableColorModel 
    {
    private:
        std::vector<ColorMesh> meshes;

        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene) noexcept;
        ColorMesh ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept;
        
    public:
        Transform transform;

        LoadableColorModel(const std::string& path, const glm::vec3& position_, 
            const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scalar_ = glm::vec3(1.0f));
        
        LoadableColorModel(const std::string& path, const glm::vec3& position_, const glm::quat& quaternion, float scale);
        LoadableColorModel(const std::string& path, const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_);
        LoadableColorModel(const std::string& path, const glm::vec3& position_, const glm::vec3& eulerAngles, float scale);

        void Draw(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#endif // __LOADABLE_COLOR_MODEL_H__
