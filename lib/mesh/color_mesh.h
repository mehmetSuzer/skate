
#ifndef __COLOR_MESH_H__
#define __COLOR_MESH_H__

#include "mesh.h"

class ColorMesh : Mesh<ColorVertex> {
public:
    ColorMesh(const std::vector<ColorVertex>& vertices_, const std::vector<GLuint>& indices_, GLenum usage);

    void Draw(const Shader& shader) const override;
    void Delete(void) const override;
};

#endif // __COLOR_MESH_H__
