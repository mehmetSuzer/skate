
#ifndef __LIGHT_MESH_H__
#define __LIGHT_MESH_H__

#include "mesh.h"

namespace skate 
{
    class LightMesh : Mesh<LightVertex> 
    {
    public:
        LightMesh(const std::vector<LightVertex>& vertices_, const std::vector<GLuint>& indices_, GLenum usage) noexcept;

        void Draw(const Shader& shader) const noexcept override;
        void Delete(void) const noexcept override;
    };
}

#endif // __COLOR_MESH_H__
