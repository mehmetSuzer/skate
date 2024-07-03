
#include "mesh.h"

Mesh::Mesh(const std::vector<PNTVertex>& vertices_, const std::vector<GLuint>& indices_, 
    const Texture2D& diffuse_, const Texture2D& specular_, const Texture2D& emission_, GLenum usage) : 
    vertices(vertices_), indices(indices_), diffuse(diffuse_), specular(specular_), emission(emission_) {
        
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PNTVertex), vertices.data(), usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), usage);

    PNTVertex::LinkAttributes();

    glBindVertexArray(0);
}

void Mesh::Draw(const Shader& shader) const {
    shader.Use();

    glActiveTexture(GL_TEXTURE0);
    shader.SetUniformInt(0, "materialMap.diffuse");
    glBindTexture(GL_TEXTURE_2D, diffuse.GetID());

    glActiveTexture(GL_TEXTURE1);
    shader.SetUniformInt(1, "materialMap.specular");
    glBindTexture(GL_TEXTURE_2D, specular.GetID());

    glActiveTexture(GL_TEXTURE2);
    shader.SetUniformInt(2, "materialMap.emission");
    glBindTexture(GL_TEXTURE_2D, emission.GetID());

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Mesh::Delete(void) const {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
