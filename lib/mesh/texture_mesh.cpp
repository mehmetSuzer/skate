
#include "texture_mesh.h"

TextureMesh::TextureMesh(const std::vector<PNTVertex>& vertices_, const std::vector<GLuint>& indices_, 
    const Texture2D& diffuse_, const Texture2D& specular_, const Texture2D& emission_, GLenum usage) : 
    Mesh<PNTVertex>(vertices_, indices_, usage), diffuse(diffuse_), specular(specular_), emission(emission_) { }

void TextureMesh::Draw(const Shader& shader) const {
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
