
#ifndef __TEXTURE_MESH_H__
#define __TEXTURE_MESH_H__

#include "mesh.h"
#include "texture2D.h"

class TextureMesh : public Mesh<TextureVertex> {
private:
    const Texture2D& diffuse;
    const Texture2D& specular;
    const Texture2D& emission;
    const float shininess;

public:
    TextureMesh(const std::vector<TextureVertex>& vertices_, const std::vector<GLuint>& indices_, 
        const Texture2D& diffuse_, const Texture2D& specular_, const Texture2D& emission_, float shininess_, GLenum usage);

    void Draw(const Shader& shader) const override;
    void Delete(void) const override;
};

#endif // __TEXTURE_MESH_H__
