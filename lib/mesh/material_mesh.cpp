
#include "material_mesh.h"

MaterialMesh::MaterialMesh(const std::vector<PNVertex>& vertices_, const std::vector<GLuint>& indices_, const Material& material_, GLenum usage) : 
    Mesh<PNVertex>(vertices_, indices_,usage), material(material_) { }

void MaterialMesh::Draw(const Shader& shader) const {
    shader.Use();

    shader.SetUniformVec3(material.ambient, "material.ambient");
    shader.SetUniformVec3(material.diffuse, "material.diffuse");
    shader.SetUniformVec3(material.specular, "material.specular");
    shader.SetUniformFloat(material.shininess, "material.shininess");

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
