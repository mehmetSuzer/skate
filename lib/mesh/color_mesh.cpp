
#include "color_mesh.h"

ColorMesh::ColorMesh(const std::vector<ColorVertex>& vertices_, const std::vector<GLuint>& indices_, GLenum usage) noexcept 
    : Mesh<ColorVertex>(vertices_, indices_, usage)  { }

void ColorMesh::Draw(const Shader& shader) const noexcept {
    shader.Use();
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void ColorMesh::Delete(void) const noexcept {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
