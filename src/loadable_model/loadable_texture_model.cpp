
#include "loadable_texture_model.h"

namespace skate 
{
    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::quat& quaternion, const glm::vec3& scalar)
        : transform(Transform(position, quaternion, scalar)) 
    { 
        LoadModel(path); 
    }
    
    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::quat& quaternion, float scale)
        : transform(Transform(position, quaternion, scale)) 
    { 
        LoadModel(path); 
    }
    
    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, const glm::vec3& scalar)
        : transform(Transform(position, eulerAngles, scalar)) 
    { 
        LoadModel(path); 
    }

    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, float scale)
        : transform(Transform(position, eulerAngles, scale)) 
    { 
        LoadModel(path); 
    }

    void LoadableTextureModel::LoadModel(const std::string& path) 
    {
        Assimp::Importer importer;
        unsigned int postProcessSteps = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
        const std::string fileExtension = path.substr(path.find_last_of('.') + 1);

        if (fileExtension == "obj") 
            postProcessSteps |= aiProcess_FlipUVs;
        
        const aiScene *scene = importer.ReadFile(path, postProcessSteps);
        assert(scene != NULL && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode != NULL); // Check import failure
        
        directory = path.substr(0, path.find_last_of('/')) + '/';
        ProcessNode(scene->mRootNode, scene);
    }

    void LoadableTextureModel::ProcessNode(aiNode* node, const aiScene* scene) noexcept 
    {
        for (uint32_t i = 0; i < node->mNumMeshes; i++) 
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++) 
            ProcessNode(node->mChildren[i], scene);
    }

    TextureMesh LoadableTextureModel::ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept 
    {
        std::vector<TextureVertex> vertices;
        std::vector<GLuint> indices;

        for (uint32_t i = 0; i < mesh->mNumVertices; i++) 
        {
            TextureVertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = (mesh->HasNormals()) ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z) : glm::vec3(0.0f);
            
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vertex.texture = (mesh->mTextureCoords[0]) ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : glm::vec2(0.0f);
            // tangents and bitangents can also be loaded when necessary
            vertices.push_back(vertex);
        }

        for (uint32_t i = 0; i < mesh->mNumFaces; i++) 
        {
            aiFace face = mesh->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; j++) 
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        const Texture& diffuse  = LoadMaterialTexture(mat, aiTextureType_DIFFUSE);
        const Texture& specular = LoadMaterialTexture(mat, aiTextureType_SPECULAR);
        const Texture& emission = LoadMaterialTexture(mat, aiTextureType_EMISSION_COLOR);

        return TextureMesh(vertices, indices, diffuse, specular, emission, 16.0f, GL_STATIC_DRAW);
    }

    const Texture& LoadableTextureModel::LoadMaterialTexture(aiMaterial *mat, aiTextureType type) noexcept 
    {
        if (mat->GetTextureCount(type) == 0)
        {
            if (type == aiTextureType_DIFFUSE || type == aiTextureType_SPECULAR)
                return Texture::white;
            if (type == aiTextureType_EMISSION_COLOR)
                return Texture::black;
        }
        
        aiString path;
        mat->GetTexture(type, 0, &path);

        for (uint32_t i = 0; i < texturesLoaded.size(); i++) 
        {
            if (texturesLoaded[i].GetPath() == directory + path.C_Str())
                return texturesLoaded[i];
        }

        Texture texture = Texture(directory + path.C_Str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
        texturesLoaded.push_back(texture);

        return texturesLoaded.back();
    }

    void LoadableTextureModel::Draw(const Shader& shader) const noexcept 
    {
        RenderState::Instance().UseShader(shader);
        shader.SetUniformMat4(transform.GetModelMatrix(), "model");
        shader.SetUniformMat3(transform.GetNormalMatrix(), "normalMatrix");

        for (uint32_t i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

    void LoadableTextureModel::DrawBorder(const Shader& shader) const noexcept
    {
        if (selected)
            Draw(shader);
    }

    void LoadableTextureModel::Delete(void) const noexcept 
    {
        for (uint32_t i = 0; i < meshes.size(); i++) 
            meshes[i].Delete();
    }
}
