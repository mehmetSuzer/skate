
#include "loadable_color_model.h"

namespace skate 
{
    LoadableColorModel::LoadableColorModel(const std::string& path, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_)
        : position(position_), rotation(rotation_), scalar(scalar_) 
    {
        LoadModel(path);
        UpdateModelAndNormalMatrices();
    }

    void LoadableColorModel::LoadModel(const std::string& path) 
    {
        Assimp::Importer importer;
        unsigned int postProcessSteps = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
        const std::string fileExtension = path.substr(path.find_last_of('.') + 1);

        if (fileExtension == "obj") 
            postProcessSteps |= aiProcess_FlipUVs;
        
        const aiScene *scene = importer.ReadFile(path, postProcessSteps);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw Exception("ERROR::ASSIMP::" + std::string(importer.GetErrorString()) + "\n");
        
        ProcessNode(scene->mRootNode, scene);
    }

    void LoadableColorModel::ProcessNode(aiNode* node, const aiScene* scene) noexcept 
    {
        for (uint32_t i = 0; i < node->mNumMeshes; i++) 
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++) 
            ProcessNode(node->mChildren[i], scene);
    }

    ColorMesh LoadableColorModel::ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept 
    {
        std::vector<ColorVertex> vertices;
        std::vector<GLuint> indices;

        aiColor4D vertexColor(1.0f);
        if (mesh->mMaterialIndex >= 0) 
            scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, vertexColor);

        for (uint32_t i = 0; i < mesh->mNumVertices; i++) 
        {
            ColorVertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = (mesh->HasNormals()) ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : glm::vec3(0.0f);
            vertex.color = glm::vec4(vertexColor.r, vertexColor.g, vertexColor.b, vertexColor.a);
            vertices.push_back(vertex);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++) 
        {
            aiFace face = mesh->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; j++) 
                indices.push_back(face.mIndices[j]);
        }

        return ColorMesh(vertices, indices, GL_STATIC_DRAW);
    }

    void LoadableColorModel::UpdateModelMatrix(void) noexcept 
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = model * glm::mat4_cast(rotation);
        model = glm::scale(model, scalar);
    }

    void LoadableColorModel::UpdateModelAndNormalMatrices(void) noexcept 
    {
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

    void LoadableColorModel::UpdatePosition(const glm::vec3& position_) noexcept 
    {
        position = position_;
        UpdateModelMatrix();
    }

    void LoadableColorModel::UpdateRotation(const glm::quat& rotation_) noexcept 
    {
        rotation = rotation_;
        UpdateModelAndNormalMatrices();
    }

    void LoadableColorModel::UpdateScalar(const glm::vec3& scalar_) noexcept 
    {
        scalar = scalar_;
        UpdateModelAndNormalMatrices();
    }

    void LoadableColorModel::Draw(const Shader& shader) const noexcept 
    {
        shader.Use();
        shader.SetUniformMat4(model, "model");
        shader.SetUniformMat3(normalMatrix, "normalMatrix");

        for (uint32_t i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

    void LoadableColorModel::Delete(void) const noexcept 
    {
        for (uint32_t i = 0; i < meshes.size(); i++) 
            meshes[i].Delete();
    }
}
