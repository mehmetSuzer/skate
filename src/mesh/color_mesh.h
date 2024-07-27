
#ifndef __COLOR_MESH_H__
#define __COLOR_MESH_H__

#include "mesh.h"

namespace skate 
{
    class ColorMesh : Mesh<ColorVertex> 
    {
    private:
        float metalness;
        float roughness;

    public:
        ColorMesh(const std::vector<ColorVertex>& vertices_, const std::vector<GLuint>& indices_, 
            float metalness_, float roughness_, GLenum usage) noexcept;

        void Draw(const Shader& shader) const noexcept override;
        void Delete(void) const noexcept override;
    };
}

#endif // __COLOR_MESH_H__
