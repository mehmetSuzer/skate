
#include "model.h"

template<typename Mesh>
Model<Mesh>::Model(
    const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_) :
    meshes(meshes_), position(position_), rotation(rotation_), scalar(scalar_) {

    UpdateMatrices();
}

template<typename Mesh>
void Model<Mesh>::UpdateMatrices(void) {
    const glm::mat3 rotation3x3 = glm::mat3_cast(rotation);
    const glm::mat4 rotation4x4 = glm::mat4(rotation3x3);
    const glm::mat3 inverseScalar3x3 = glm::mat3(1.0f/scalar.x, 0.0f, 0.0f, 0.0f, 1.0f/scalar.y, 0.0f, 0.0f, 0.0f, 1.0f/scalar.z);

    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = model * rotation4x4;
    model = glm::scale(model, scalar);

    // normalMatrix = the upper left 3x3 matrix of the transpose of the inverse of the model matrix
    // the following calculation is the simplified version
    normalMatrix = rotation3x3 * inverseScalar3x3;
}

template<typename Mesh>
void Model<Mesh>::UpdatePosition(const glm::vec3& position_) {
    position = position_;
    UpdateMatrices();
}

template<typename Mesh>
void Model<Mesh>::UpdateRotation(const glm::quat& rotation_) {
    rotation = rotation_;
    UpdateMatrices();
}

template<typename Mesh>
void Model<Mesh>::UpdateScalar(const glm::vec3& scalar_) {
    scalar = scalar_;
    UpdateMatrices();
}

template<typename Mesh>
void Model<Mesh>::Draw(const Shader& shader, const glm::mat4& projectionView, const glm::vec3& cameraPosition, const Light& light) const {
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

template<typename Mesh>
void Model<Mesh>::Delete(void) const {
    for (uint32_t i = 0; i < meshes.size(); i++) {
        meshes[i].Delete();
    }
}
