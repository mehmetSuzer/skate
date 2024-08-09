
#ifndef __TEXTURE_MESH_H__
#define __TEXTURE_MESH_H__

#include "mesh.h"
#include "texture.h"

namespace skate 
{
    class TextureMesh : public Mesh<TextureVertex> 
    {
    private:
        const Texture diffuse;
        const Texture specular;
        const Texture emission;
        const float shininess;

    public:
        TextureMesh(const std::vector<TextureVertex>& vertices_, const std::vector<GLuint>& indices_, 
            const Texture& diffuse_, const Texture& specular_ = Texture::white, const Texture& emission_ = Texture::black, 
            float shininess_ = 16.0f, GLenum usage = GL_STATIC_DRAW) noexcept;

        void Draw(const Shader& shader) const noexcept override;
        void Delete(void) const noexcept override;
    };
}

#endif // __TEXTURE_MESH_H__
