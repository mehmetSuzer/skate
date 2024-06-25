
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <common.h>
#include <spot_light.h>

enum AxisDirection {
    AXIS_NONE = 0,
    AXIS_POSITIVE,
    AXIS_NEGATIVE,
};

typedef struct {
    enum AxisDirection right;
    enum AxisDirection up;
    enum AxisDirection forward;
} CameraDirection;

class Camera {
private:
    static Camera instance;
    bool initialized = false;

    static constexpr float lowSpeed = 0.8f; 
    static constexpr float highSpeed = 3.0f * lowSpeed;
    static constexpr float maxPitch = M_PIf * 85.0f / 180.0f;
    static constexpr float minFOVradian = M_PIf / 90.0f;
    static constexpr float maxFOVradian = M_PIf / 3.0f;
    static constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitch = 0.0f;
    float yaw = -M_PIf / 2.0f;
    
    float FOVradian = M_PIf / 4.0f;
    float near = 0.1f;
    float far = 100.0f;

    CameraDirection direction = {AXIS_NONE, AXIS_NONE, AXIS_NONE};
    float speed = lowSpeed;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 right;
    glm::vec3 forward;

    glm::mat4 view;
    glm::mat4 projection;

    SpotLight flashLight = SpotLight(position, 0.07f, 0.017f, glm::vec3(0.0f, 0.0f, -1.0f), M_PIf/12.0f, M_PIf/6.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    Camera() {}

public:
    static Camera& Instance(void) {
        return instance;
    }

    const glm::vec3& GetPosition(void) const {
        return position;
    }

    const glm::mat4& GetView(void) const {
        return view;
    }

    const glm::mat4& GetProjection(void) const {
        return projection;
    }

    void SetRightDirection(enum AxisDirection axisDirection) {
        direction.right = axisDirection;
    }

    void SetUpDirection(enum AxisDirection axisDirection) {
        direction.up = axisDirection;
    }

    void SetForwardDirection(enum AxisDirection axisDirection) {
        direction.forward = axisDirection;
    }

    void SetLowSpeed(void) {
        speed = lowSpeed;
    }

    void SetHighSpeed(void) {
        speed = highSpeed;
    }

    void UpdateView(void) {
        view = glm::lookAt(position, position + forward, up);
    }

    void UpdateProjection(void) {
        projection = glm::perspective(FOVradian, Common::Instance().GetAspectRatio(), near, far);
    }

    const SpotLight& GetFlashLight(void) const {
        return flashLight;
    }

    void ToggleFlashLight(void) {
        flashLight.Toggle();
    }

    void UpdateVectors(void);
    void UpdateFlashLight(void);
    void Initialize(void);
    void UpdateFOVradian(float deltaFOVradian);
    void UpdatePosition(float elapsedTimeSinceLastFrame);
    void UpdateOrientation(float xOffset, float yOffset);
};

#endif // __CAMERA_H__
