
#ifndef __MODEL_H__
#define __MODEL_H__

#include "light.h"
#include "color_mesh.h"
#include "material_mesh.h"
#include "texture_mesh.h"

// Update shaders as well when you update this
#define MAX_LIGHT_CASTER_NUMBER 8

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
    Model(const std::vector<Mesh>& meshes_, const glm::vec3& position_, const glm::quat& rotation_, const glm::vec3& scalar_);

    void UpdateMatrices(void);
    void UpdatePosition(const glm::vec3& position_);
    void UpdateRotation(const glm::quat& rotation_);
    void UpdateScalar(const glm::vec3& scalar_);

    void Draw(const Shader& shader, const glm::mat4& projectionView, 
        const glm::vec3& cameraPosition, const std::vector<LightCaster*>& lightCasters) const;
    void Delete(void) const;
};

#include "model.cpp"

#endif // __MODEL_H__
