
#ifndef __MATERIAL_MESH_H__
#define __MATERIAL_MESH_H__

#include "mesh.h"
#include "material.h"

class MaterialMesh : public Mesh<MaterialVertex> {
private:
    const Material material;

public:
    MaterialMesh(const std::vector<MaterialVertex>& vertices_, const std::vector<GLuint>& indices_, 
        const Material& material_, GLenum usage) noexcept;

    void Draw(const Shader& shader) const noexcept override;
    void Delete(void) const noexcept override;
};

#endif // __MATERIAL_MESH_H__
