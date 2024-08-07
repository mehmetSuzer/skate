
#ifndef __MESH_H__
#define __MESH_H__

#include "vertex.h"
#include "shader.h"

namespace skate 
{
    // The simplest drawable structure which contains the vertices and indices of an object.
    // Vertex must be one of LightVertex, ColorVertex, MaterialVertex, and TextureVertex!
    template<typename Vertex>
    class Mesh 
    {
    static_assert(
        isAValidVertex<Vertex>::value, 
        "Vertex must be one of LightVertex, ColorVertex, MaterialVertex, and TextureVertex!"
    );

    protected:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        const std::vector<Vertex> vertices;
        const std::vector<GLuint> indices;

    public:
        Mesh(const std::vector<Vertex>& vertices_, const std::vector<GLuint>& indices_, GLenum usage) noexcept 
            : vertices(vertices_), indices(indices_) 
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), usage);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), usage);

            Vertex::LinkAttributes();
            glBindVertexArray(0);
        }

        virtual ~Mesh() noexcept {}

        virtual void Draw(const Shader& shader) const noexcept = 0;
        virtual void Delete(void) const noexcept = 0;
    };
}

#endif // __MESH_H__
