
#include "loadable_color_model.h"

namespace skate 
{
    LoadableColorModel::LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::quat& quaternion, const glm::vec3& scalar)
        : transform(Transform(position, quaternion, scalar)) 
    { 
        LoadModel(path); 
    }
    
    LoadableColorModel::LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::quat& quaternion, float scale)
        : transform(Transform(position, quaternion, scale)) 
    { 
        LoadModel(path); 
    }
    
    LoadableColorModel::LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, const glm::vec3& scalar)
        : transform(Transform(position, eulerAngles, scalar)) 
    { 
        LoadModel(path); 
    }

    LoadableColorModel::LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, float scale)
        : transform(Transform(position, eulerAngles, scale)) 
    { 
        LoadModel(path); 
    }

    void LoadableColorModel::LoadModel(const std::string& path) 
    {
        Assimp::Importer importer;
        unsigned int postProcessSteps = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
        const std::string fileExtension = path.substr(path.find_last_of('.') + 1);

        if (fileExtension == "obj") 
            postProcessSteps |= aiProcess_FlipUVs;
        
        const aiScene *scene = importer.ReadFile(path, postProcessSteps);
        assert(scene != NULL && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode != NULL); // Check import failure
        
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

        // Default values
        aiColor4D vertexColor(1.0f);
        float metalness = 0.0f;
        float roughness = 0.0f;

        // Values are not affected if Get does not return aiReturn_SUCCESS
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, vertexColor);
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_METALLIC_FACTOR, metalness);
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);

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

        return ColorMesh(vertices, indices, metalness, roughness, GL_STATIC_DRAW);
    }

    void LoadableColorModel::Draw(const Shader& shader) const noexcept 
    {
        shader.Use();
        shader.SetUniformMat4(transform.GetModelMatrix(), "model");
        shader.SetUniformMat3(transform.GetNormalMatrix(), "normalMatrix");

        for (uint32_t i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

    void LoadableColorModel::DrawBorder(const Shader& shader) const noexcept
    {
        if (selected)
            Draw(shader);
    }

    void LoadableColorModel::Delete(void) const noexcept 
    {
        for (uint32_t i = 0; i < meshes.size(); i++) 
            meshes[i].Delete();
    }
}
