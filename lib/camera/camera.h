
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <common.h>

typedef enum {
    AXIS_NONE,
    AXIS_POSITIVE,
    AXIS_NEGATIVE,
} AXIS_DIRECTION;

typedef struct {
    AXIS_DIRECTION right;
    AXIS_DIRECTION up;
    AXIS_DIRECTION forward;
} CameraDirection;

class Camera {
private:
    static Camera instance;
    bool initialized = false;

    static constexpr float lowSpeed = 0.8f; 
    static constexpr float highSpeed = 2.4f;
    static constexpr float maxPitch = M_PIf * 89.0f / 180.0f;
    static constexpr float mouseSensitivity = M_PIf / 1800.0f;
    static constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitch;
    float yaw;
    
    float FOVradian;
    float near;
    float far;

    CameraDirection direction;
    float speed;

    glm::vec3 forward;
    glm::vec3 position;
    glm::vec3 right;

    glm::mat4 view;
    glm::mat4 perspective;

    Camera() {}

public:
    static Camera& Instance(void) {
        return instance;
    }

    void Initialize(void) {
        if (initialized) {
            return;
        }
        initialized = true;

        pitch = 0.0f;
        yaw = -M_PIf / 2.0f;
        
        FOVradian = M_PIf / 4.0f;
        near = 0.1f;
        far = 100.0f;

        direction = {AXIS_NONE, AXIS_NONE, AXIS_NONE};
        speed = lowSpeed;

        forward = glm::vec3(
            cosf(yaw) * cosf(pitch),    // x
            sinf(pitch),                // y
            sinf(yaw) * cosf(pitch)     // z
        );

        position = glm::vec3(0.0f, 0.0f, 0.0f);
        right = glm::normalize(glm::cross(forward, up));

        view = glm::lookAt(position, position + forward, up);
        perspective = glm::perspective(FOVradian, Common::Instance().GetAspectRatio(), near, far);
    }

    const glm::mat4& GetView(void) const {
        return view;
    }

    const glm::mat4& GetPerspective(void) const {
        return perspective;
    }

    void SetRightDirection(AXIS_DIRECTION axisDirection) {
        direction.right = axisDirection;
    }

    void SetUpDirection(AXIS_DIRECTION axisDirection) {
        direction.up = axisDirection;
    }

    void SetForwardDirection(AXIS_DIRECTION axisDirection) {
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

    void UpdatePerspective(void) {
        perspective = glm::perspective(FOVradian, Common::Instance().GetAspectRatio(), near, far);
    }

    void UpdatePosition(float elapsedTimeSinceLastFrame);
    void UpdateOrientation(float xOffset, float yOffset);
};

#endif // __CAMERA_H__
