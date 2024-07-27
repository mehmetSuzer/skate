
#ifndef __LOADABLE_TEXTURE_MODEL_H__
#define __LOADABLE_TEXTURE_MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "transform.h"
#include "texture_mesh.h"

namespace skate 
{
    // Models that have more than one material map for a type is not supported. 
    // For instance, a model having 2 albedo maps cannot be loaded fully. One of the albedo maps is discarded.
    // In such cases, either combine the textures in one image, or split the model into several models.
    class LoadableTextureModel 
    {
    private:
        std::vector<TextureMesh> meshes;
        std::vector<Texture> texturesLoaded;
        std::string directory;

        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene) noexcept;
        TextureMesh ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept;
        const Texture& LoadMaterialTexture(aiMaterial *mat, aiTextureType type) noexcept;
        
    public:
        Transform transform;

        LoadableTextureModel(const std::string& path, const glm::vec3& position, 
            const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scalar = glm::vec3(1.0f));
        
        LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::quat& quaternion, float scale);
        LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, const glm::vec3& scalar);
        LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, float scale);

        void Draw(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#endif // __LOADABLE_TEXTURE_MODEL_H__
