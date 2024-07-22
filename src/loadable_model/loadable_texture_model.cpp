
#include "loadable_texture_model.h"

namespace skate 
{
    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::quat& quaternion, const glm::vec3& scalar_)
        : transform(Transform(position_, quaternion, scalar_)) 
    { 
        LoadModel(path); 
    }
    
    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::quat& quaternion, float scale)
        : transform(Transform(position_, quaternion, scale)) 
    { 
        LoadModel(path); 
    }
    
    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::vec3& eulerAngles, const glm::vec3& scalar_)
        : transform(Transform(position_, eulerAngles, scalar_)) 
    { 
        LoadModel(path); 
    }

    LoadableTextureModel::LoadableTextureModel(const std::string& path, const glm::vec3& position_, const glm::vec3& eulerAngles, float scale)
        : transform(Transform(position_, eulerAngles, scale)) 
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
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw Exception("ERROR::ASSIMP::" + std::string(importer.GetErrorString()) + "\n");
        
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
        std::vector<Texture> diffuseMaps;
        std::vector<Texture> specularMaps;
        std::vector<Texture> emissionMaps;

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

        if (mesh->mMaterialIndex >= 0) 
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
            specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
            emissionMaps = LoadMaterialTextures(material, aiTextureType_EMISSION_COLOR);
        }

        const Texture& diffuse  = (diffuseMaps.empty())  ? Texture::white : diffuseMaps[0];
        const Texture& specular = (specularMaps.empty()) ? Texture::white : specularMaps[0];
        const Texture& emission = (emissionMaps.empty()) ? Texture::black : emissionMaps[0];

        return TextureMesh(vertices, indices, diffuse, specular, emission, 16.0f, GL_STATIC_DRAW);
    }

    std::vector<Texture> LoadableTextureModel::LoadMaterialTextures(aiMaterial *mat, aiTextureType type) noexcept 
    {
        std::vector<Texture> textures;
        for (uint32_t i = 0; i < mat->GetTextureCount(type); i++) 
        {
            aiString path;
            mat->GetTexture(type, i, &path);
            bool skip = false;

            for (uint32_t j = 0; j < texturesLoaded.size(); j++) 
            {
                if (texturesLoaded[j].GetPath() == directory + std::string(path.C_Str())) 
                {
                    textures.push_back(texturesLoaded[j]);
                    skip = true;
                    break;
                }
            }

            if (!skip) 
            {
                Texture texture = Texture(directory + path.C_Str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
                textures.push_back(texture);
                texturesLoaded.push_back(texture);
            }
        }
        return textures;
    }

    void LoadableTextureModel::Draw(const Shader& shader) const noexcept 
    {
        shader.Use();
        shader.SetUniformMat4(transform.GetModelMatrix(), "model");
        shader.SetUniformMat3(transform.GetNormalMatrix(), "normalMatrix");

        for (uint32_t i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

    void LoadableTextureModel::Delete(void) const noexcept 
    {
        for (uint32_t i = 0; i < meshes.size(); i++) 
            meshes[i].Delete();
    }
}
