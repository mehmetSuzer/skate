
#ifndef __COLOR_MESH_H__
#define __COLOR_MESH_H__

#include "mesh.h"

class ColorMesh : Mesh<ColorVertex> {
public:
    ColorMesh(const std::vector<ColorVertex>& vertices_, const std::vector<GLuint>& indices_, GLenum usage) noexcept;

    void Draw(const Shader& shader) const noexcept override;
    void Delete(void) const noexcept override;
};

#endif // __COLOR_MESH_H__
