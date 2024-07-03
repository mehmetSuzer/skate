
#include "color_mesh.h"

ColorMesh::ColorMesh(const std::vector<PNCVertex>& vertices_, const std::vector<GLuint>& indices_, GLenum usage) : 
    Mesh<PNCVertex>(vertices_, indices_, usage)  { }

void ColorMesh::Draw(const Shader& shader) const {
    shader.Use();
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
