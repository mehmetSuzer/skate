
#ifndef __TEXTURE_MESH_H__
#define __TEXTURE_MESH_H__

#include "mesh.h"
#include "texture2D.h"

class TextureMesh : public Mesh<PNTVertex> {
private:
    const Texture2D& diffuse;
    const Texture2D& specular;
    const Texture2D& emission;

public:
    TextureMesh(const std::vector<PNTVertex>& vertices_, const std::vector<GLuint>& indices_, 
        const Texture2D& diffuse_, const Texture2D& specular_, const Texture2D& emission_, GLenum usage);

    void Draw(const Shader& shader) const override;
};

#endif // __TEXTURE_MESH_H__
