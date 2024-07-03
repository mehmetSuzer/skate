
#ifndef __MODEL_H__
#define __MODEL_H__

#include "light.h"
#include "color_mesh.h"
#include "material_mesh.h"
#include "texture_mesh.h"

template<typename Mesh>
class Model {
private:
    const std::vector<Mesh>& meshes;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scalar;

    glm::mat4 model;
    glm::mat4 normalMatrix;

public:
    Model(
        const std::vector<Mesh>& meshes_, const glm::vec3& position_, 
        const glm::quat& rotation_, const glm::vec3& scalar_) :
        meshes(meshes_), position(position_), rotation(rotation_), scalar(scalar_) {

        UpdateMatrices();
    }

    void UpdateMatrices(void) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = model * glm::mat4_cast(rotation);
        model = glm::scale(model, scalar);
        normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
    }

    void UpdatePosition(const glm::vec3& position_) {
        position = position_;
        UpdateMatrices();
    }

    void UpdateRotation(const glm::quat& rotation_) {
        rotation = rotation_;
        UpdateMatrices();
    }

    void UpdateScalar(const glm::vec3& scalar_) {
        scalar = scalar_;
        UpdateMatrices();
    }

    void Draw(const Shader& shader, const glm::mat4& projectionView, const glm::vec3& cameraPosition, const Light& light) const {
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

    // Textures in meshes are not deleted in this method,
    // in case there are other meshes using same textures
    // void Delete(void) const {
    //     for (uint32_t i = 0; i < meshes.size(); i++) {
    //         meshes[i].Delete();
    //     }
    // }
};

#endif // __MODEL_H__
