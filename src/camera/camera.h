
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "util.h"
#include "transform.h"

namespace skate 
{
    enum AxisDirection 
    {
        AXIS_NONE = 0,
        AXIS_POSITIVE,
        AXIS_NEGATIVE,
    };

    typedef struct 
    {
        enum AxisDirection right;
        enum AxisDirection up;
        enum AxisDirection forward;
    } CameraDirection;

    // First person camera where vertical roll is prevented
    class Camera 
    {
    private:
        CameraDirection direction = {AXIS_NONE, AXIS_NONE, AXIS_NONE};

        const float maxCosAngleBetweenForwardAndWorldUp = glm::cos(M_PIf / 36.0f);

        static constexpr float lowSpeed = 2.0f; 
        static constexpr float highSpeed = 3.0f * lowSpeed;
        float speed = lowSpeed;

        const float minFOVRadian;
        const float maxFOVRadian;
        float FOVRadian;

        const float near;
        const float far;

        glm::mat4 view;
        glm::mat4 projection;

        inline void UpdateView(void) noexcept 
        {
            const glm::vec3& position = transform.GetPosition();
            const glm::vec3& forward = transform.GetForward();
            view = glm::lookAt(position, position + forward, Transform::WorldUp);
        }

    public:
        Transform transform;

        Camera(const glm::vec3& position, float near_ = 0.1f, float far_ = 100.0f, float FOVRadian_ = M_PIf/4.0f, 
            float minFOVRadian_ = M_PIf/90.0f, float maxFOVRadian_ = M_PIf/3.0f);

        inline const glm::mat4& GetView(void) const noexcept 
        {
            return view;
        }

        inline const glm::mat4& GetProjection(void) const noexcept 
        {
            return projection;
        }

        inline void SetRightDirection(enum AxisDirection axisDirection) noexcept 
        {
            direction.right = axisDirection;
        }

        inline void SetUpDirection(enum AxisDirection axisDirection) noexcept 
        {
            direction.up = axisDirection;
        }

        inline void SetForwardDirection(enum AxisDirection axisDirection) noexcept 
        {
            direction.forward = axisDirection;
        }

        inline void SetLowSpeed(void) noexcept 
        {
            speed = lowSpeed;
        }

        inline void SetHighSpeed(void) noexcept 
        {
            speed = highSpeed;
        }

        inline void UpdateProjection(void) noexcept 
        {
            projection = glm::perspective(FOVRadian, util::aspectRatio, near, far);
        }

        // Use this function in mouse scroll callback
        void UpdateFOVRadian(float deltaFOVRadian) noexcept;

        // use this function in main loop
        void UpdatePosition(float elapsedTimeSinceLastFrame) noexcept;
        
        // Use this function in cursor position callback
        void UpdateOrientation(float xOffset, float yOffset) noexcept;
    };
}

#endif // __CAMERA_H__
