
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
            float metalness_ = 1.0f, float roughness_ = 0.0f, GLenum usage = GL_STATIC_DRAW) noexcept;

        void Draw(const Shader& shader) const noexcept override;
        void Delete(void) const noexcept override;
    };
}

#endif // __COLOR_MESH_H__
