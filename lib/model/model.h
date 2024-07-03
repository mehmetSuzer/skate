
#ifndef __MODEL_H__
#define __MODEL_H__

#include <mesh.h>

class Model {
private:
    std::vector<Mesh> meshes;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scalar;

    glm::mat4 model;
    glm::mat4 normalMatrix;

public:
    Model(
        const std::vector<Mesh>& meshes_, 
        const glm::vec3& position_, 
        const glm::quat& rotation_, 
        const glm::vec3& scalar_
    );

    void UpdateMatrices(void);
    void UpdatePosition(const glm::vec3& position_);
    void UpdateRotation(const glm::quat& rotation_);
    void UpdateScalar(const glm::vec3& scalar_);

    void Draw(const Shader& shader, const glm::mat4& projectionView, const glm::vec3& cameraPosition, const Light& light) const;
    void Delete(void) const;
};

#endif // __MODEL_H__
