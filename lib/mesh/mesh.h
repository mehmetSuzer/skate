
#ifndef __MESH_H__
#define __MESH_H__

#include "vbo.h"
#include "light.h"
#include "texture2D.h"
#include "shader.h"

class Mesh {
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const std::vector<PNTVertex>& vertices;
    const std::vector<GLuint>& indices;
    const Texture2D& diffuse;
    const Texture2D& specular;
    const Texture2D& emission;

public:
    Mesh(const std::vector<PNTVertex>& vertices_, const std::vector<GLuint>& indices_, 
        const Texture2D& diffuse_, const Texture2D& specular_, const Texture2D& emission_, GLenum usage);

    void Draw(const Shader& shader) const;

    // Textures are not deleted in this method,
    // in case there are other meshes using same textures
    void Delete(void) const;
};

#endif // __MESH_H__
