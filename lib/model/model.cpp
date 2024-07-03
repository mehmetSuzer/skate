
#include "model.h"

Model::Model(
    const std::vector<Mesh>& meshes_, const glm::vec3& position_, 
    const glm::quat& rotation_, const glm::vec3& scalar_) :
    meshes(meshes_), position(position_), rotation(rotation_), scalar(scalar_) {

    UpdateMatrices();
}

void Model::UpdateMatrices(void) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
	model = model * glm::mat4_cast(rotation);
    model = glm::scale(model, scalar);
    normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
}
    
void Model::UpdatePosition(const glm::vec3& position_) {
    position = position_;
    UpdateMatrices();
}
    
void Model::UpdateRotation(const glm::quat& rotation_) {
    rotation = rotation_;
    UpdateMatrices();
}

void Model::UpdateScalar(const glm::vec3& scalar_) {
    scalar = scalar_;
    UpdateMatrices();
}

void Model::Draw(const Shader& shader, const glm::mat4& projectionView, const glm::vec3& cameraPosition, const Light& light) const {
    shader.Use();
    shader.SetUniformMat4(model, "model");
    shader.SetUniformMat3(normalMatrix, "normalMatrix");

    shader.SetUniformMat4(projectionView, "projectionView");
    shader.SetUniformVec3(cameraPosition, "cameraPosition");

    shader.SetUniformInt(light.type, "light.type");
    shader.SetUniformVec3(light.color, "light.color");
    shader.SetUniformVec3(light.position, "light.position");
    shader.SetUniformVec3(light.direction, "light.direction");
    shader.SetUniformFloat(light.intensity, "light.intensity");
    shader.SetUniformFloat(light.linear, "light.linear");
    shader.SetUniformFloat(light.quadratic, "light.quadratic");
    shader.SetUniformFloat(light.cosInnerCutOff, "light.cosInnerCutOff");
    shader.SetUniformFloat(light.cosOuterCutOff, "light.cosOuterCutOff");

    for (uint32_t i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}

void Model::Delete(void) const {
    for (uint32_t i = 0; i < meshes.size(); i++) {
        meshes[i].Delete();
    }
}
