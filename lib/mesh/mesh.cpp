
#include "mesh.h"

Mesh::Mesh(const std::vector<PNTVertex>& vertices_, const std::vector<GLuint>& indices_, 
    const std::vector<Texture2D>& textures_, GLenum usage) : 
    vertices(vertices_), indices(indices_), textures(textures_) {
        
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

    GLuint diffuseIndex = 0;
    GLuint specularIndex = 0;
    GLuint emissionIndex = 0;

    for (uint32_t unit = 0; unit < textures.size(); unit++) {
        glActiveTexture(GL_TEXTURE0 + unit);
        std::string number;
        const std::string& type = textures[unit].GetType();

        if (type == "diffuse") {
            number = std::to_string(diffuseIndex++);
        } else if (type == "specular") {
            number = std::to_string(specularIndex++);
        } else if (type == "emission") {
            number = std::to_string(emissionIndex++);
        } else {
            continue;
        }
        shader.SetUniformInt(unit, ("materialMap[" + number + "]." + type).c_str());
        glBindTexture(GL_TEXTURE_2D, textures[unit].GetID());
    }

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
