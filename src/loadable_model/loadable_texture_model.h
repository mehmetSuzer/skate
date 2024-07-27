
#ifndef __LOADABLE_TEXTURE_MODEL_H__
#define __LOADABLE_TEXTURE_MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "transform.h"
#include "texture_mesh.h"

namespace skate 
{
    class LoadableTextureModel 
    {
    private:
        std::vector<TextureMesh> meshes;
        std::vector<Texture> texturesLoaded;
        std::string directory;

        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene) noexcept;
        TextureMesh ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept;
        std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type) noexcept;
        
    public:
        Transform transform;

        LoadableTextureModel(const std::string& path, const glm::vec3& position_, 
            const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scalar_ = glm::vec3(1.0f));
        
        LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::quat& quaternion, float scale);
        LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_);
        LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::vec3& eulerAngles, float scale);

        void Draw(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#endif // __LOADABLE_TEXTURE_MODEL_H__
