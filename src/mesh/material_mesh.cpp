
#include "material_mesh.h"

namespace skate 
{
    MaterialMesh::MaterialMesh(const std::vector<MaterialVertex>& vertices_, const std::vector<GLuint>& indices_, 
        const Material& material_, GLenum usage) noexcept 
        : Mesh<MaterialVertex>(vertices_, indices_,usage), material(material_) {}

    void MaterialMesh::Draw(const Shader& shader) const noexcept 
    {
        RenderState::Instance().UseShader(shader);
        shader.SetUniformVec3(material.ambient, "material.ambient");
        shader.SetUniformVec3(material.diffuse, "material.diffuse");
        shader.SetUniformVec3(material.specular, "material.specular");
        shader.SetUniformFloat(material.shininess, "material.shininess");

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
    }

    void MaterialMesh::Delete(void) const noexcept 
    {
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
}
