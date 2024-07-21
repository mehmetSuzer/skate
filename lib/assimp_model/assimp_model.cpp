
#include "assimp_model.h"

AssimpModel::AssimpModel(const std::string& path, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_)
    : position(position_), rotation(rotation_), scalar(scalar_) {

    LoadModel(path);
    UpdateModelAndNormalMatrices();
}

void AssimpModel::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    unsigned int postProcessSteps = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
    const std::string fileExtension = path.substr(path.find_last_of('.') + 1);
    if (fileExtension == "obj") {
        postProcessSteps |= aiProcess_FlipUVs;
    }
    
    const aiScene *scene = importer.ReadFile(path, postProcessSteps);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        const std::string message = "ERROR::ASSIMP::" + std::string(importer.GetErrorString()) + "\n";
        throw Exception(message);
    }
    directory = path.substr(0, path.find_last_of('/')) + '/';
    ProcessNode(scene->mRootNode, scene);
}

void AssimpModel::ProcessNode(aiNode* node, const aiScene* scene) noexcept {
    for (uint32_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

TextureMesh AssimpModel::ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept {
    std::vector<TextureVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture2D> diffuseMaps;
    std::vector<Texture2D> specularMaps;
    std::vector<Texture2D> emissionMaps;

    const Texture2D blackTexture = Texture2D(util::texturesPath + "black.jpg", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
    const Texture2D whiteTexture = Texture2D(util::texturesPath + "white.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);

    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
        TextureVertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = (mesh->HasNormals()) ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : glm::vec3(0.0f, 0.0f, 0.0f);
        
        // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
        // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
        vertex.texture = (mesh->mTextureCoords[0]) ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : glm::vec2(0.0f, 0.0f);
        // tangents and bitangents can also be loaded when necessary
        vertices.push_back(vertex);
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (uint32_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
        specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
        emissionMaps = LoadMaterialTextures(material, aiTextureType_EMISSION_COLOR);
    }
    const Texture2D& diffuse = (diffuseMaps.empty()) ? whiteTexture : diffuseMaps[0];
    const Texture2D& specular = (specularMaps.empty()) ? whiteTexture : specularMaps[0];
    const Texture2D& emission = (emissionMaps.empty()) ? blackTexture : emissionMaps[0];

    return TextureMesh(vertices, indices, diffuse, specular, emission, 16.0f, GL_STATIC_DRAW);
}

std::vector<Texture2D> AssimpModel::LoadMaterialTextures(aiMaterial *mat, aiTextureType type) noexcept {
    std::vector<Texture2D> textures;
    for (uint32_t i = 0; i < mat->GetTextureCount(type); i++) {
        aiString path;
        mat->GetTexture(type, i, &path);
        bool skip = false;

        for (uint32_t j = 0; j < texturesLoaded.size(); j++) {
            if (texturesLoaded[j].GetPath() == directory + std::string(path.C_Str())) {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture2D texture = Texture2D(directory + path.C_Str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
            textures.push_back(texture);
            texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

void AssimpModel::UpdateModelMatrix(void) noexcept {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = model * glm::mat4_cast(rotation);
    model = glm::scale(model, scalar);
}

void AssimpModel::UpdateModelAndNormalMatrices(void) noexcept {
    const glm::mat3 rotation3x3 = glm::mat3_cast(rotation);
    const glm::mat4 rotation4x4 = glm::mat4(rotation3x3);
    const glm::mat3 inverseScalar3x3 = glm::mat3(1.0f/scalar.x, 0.0f, 0.0f, 0.0f, 1.0f/scalar.y, 0.0f, 0.0f, 0.0f, 1.0f/scalar.z);

    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = model * rotation4x4;
    model = glm::scale(model, scalar);

    // normalMatrix = the upper left 3x3 matrix of the transpose of the inverse of the model matrix
    // the following calculation is mathematically the simplified version
    normalMatrix = rotation3x3 * inverseScalar3x3;
}

void AssimpModel::UpdatePosition(const glm::vec3& position_) noexcept {
    position = position_;
    UpdateModelMatrix();
}

void AssimpModel::UpdateRotation(const glm::quat& rotation_) noexcept {
    rotation = rotation_;
    UpdateModelAndNormalMatrices();
}

void AssimpModel::UpdateScalar(const glm::vec3& scalar_) noexcept {
    scalar = scalar_;
    UpdateModelAndNormalMatrices();
}

void AssimpModel::Draw(const Shader& shader) const noexcept {
    shader.Use();
    shader.SetUniformMat4(model, "model");
    shader.SetUniformMat3(normalMatrix, "normalMatrix");

    for (uint32_t i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}

void AssimpModel::Delete(void) const noexcept {
    for (uint32_t i = 0; i < meshes.size(); i++) {
        meshes[i].Delete();
    }
}
