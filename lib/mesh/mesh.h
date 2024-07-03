
#ifndef __MESH_H__
#define __MESH_H__

#include <vbo.h>
#include <light.h>
#include <texture2D.h>
#include <shader.h>

class Mesh {
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<PNTVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture2D> textures;

public:
    Mesh(
        const std::vector<PNTVertex>& vertices_, 
        const std::vector<GLuint>& indices_, 
        const std::vector<Texture2D>& textures_, 
        GLenum usage
    );

    void Draw(const Shader& shader) const;
    void Delete(void) const;
};

#endif // __MESH_H__
