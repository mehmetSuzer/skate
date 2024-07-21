
#ifndef __ASSIMP_MODEL_H__
#define __ASSIMP_MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "light.h"
#include "texture_mesh.h"
#include "gtc/type_ptr.hpp"

class AssimpModel {
private:
    std::vector<TextureMesh> meshes;
    std::vector<Texture2D> texturesLoaded;
    std::string directory;

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scalar;

    glm::mat4 model;
    glm::mat4 normalMatrix;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene) noexcept;
    TextureMesh ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept;
    std::vector<Texture2D> LoadMaterialTextures(aiMaterial *mat, aiTextureType type) noexcept;
    
public:
    AssimpModel(const std::string& path, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_);

    void UpdateModelMatrix(void) noexcept;
    void UpdateModelAndNormalMatrices(void) noexcept;
    void UpdatePosition(const glm::vec3& position_) noexcept;
    void UpdateRotation(const glm::quat& rotation_) noexcept;
    void UpdateScalar(const glm::vec3& scalar_) noexcept;

    void Draw(const Shader& shader) const noexcept;
    void Delete(void) const noexcept;
};

#endif // __ASSIMP_MODEL_H__
