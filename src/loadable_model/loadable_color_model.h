
#ifndef __LOADABLE_COLOR_MODEL_H__
#define __LOADABLE_COLOR_MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "transform.h"
#include "color_mesh.h"

namespace skate 
{
    // For models that have vertex colors but not material maps.
    class LoadableColorModel 
    {
    private:
        bool selected = false;
        std::vector<ColorMesh> meshes;

        void LoadModel(const std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene) noexcept;
        ColorMesh ProcessMesh(aiMesh *mesh, const aiScene *scene) noexcept;
        
    public:
        Transform transform;

        LoadableColorModel(const std::string& path, const glm::vec3& position, 
            const glm::quat& quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scalar = glm::vec3(1.0f));
        
        LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::quat& quaternion, float scale);
        LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, const glm::vec3& scalar);
        LoadableColorModel(const std::string& path, const glm::vec3& position, const glm::vec3& eulerAngles, float scale);

        inline void Select(void) noexcept
        {
            selected = true;
        }

        inline void Unselected(void) noexcept
        {
            selected = false;
        }
        
        void Draw(const Shader& shader) const noexcept;
        void DrawBorder(const Shader& shader) const noexcept;
        void Delete(void) const noexcept;
    };
}

#endif // __LOADABLE_COLOR_MODEL_H__
