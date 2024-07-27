
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "util.h"
#include "gtc/type_ptr.hpp"

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

    // Singleton first person camera where vertical roll is prevented
    class Camera 
    {
    private:
        static Camera instance;
        bool initialized = false;

        const float lowSpeed = 1.6f; 
        const float highSpeed = 3.0f * lowSpeed;
        const float maxPitch = M_PIf * 85.0f / 180.0f;
        const float minFOVradian = M_PIf / 90.0f;
        const float maxFOVradian = M_PIf / 3.0f;
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        float pitch = 0.0f;
        float yaw = M_PIf / 2.0f;
        
        float FOVradian = M_PIf / 4.0f;
        float near = 0.1f;
        float far = 100.0f;

        CameraDirection direction = {AXIS_NONE, AXIS_NONE, AXIS_NONE};
        float speed = lowSpeed;

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 right;
        glm::vec3 forward;

        glm::mat4 view;
        glm::mat4 projection;

        void UpdateVectors(void) noexcept;

        inline void UpdateView(void) noexcept 
        {
            view = glm::lookAt(position, position + forward, up);
        }

    public:
        inline static Camera& Instance(void) noexcept 
        {
            return instance;
        }

        inline const glm::vec3& GetPosition(void) const noexcept 
        {
            return position;
        }

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
            projection = glm::perspective(FOVradian, util::aspectRatio, near, far);
        }

        void Initialize(void) noexcept;

        // Use this function in mouse scroll callback
        void UpdateFOVradian(float deltaFOVradian) noexcept;

        // use this function in main loop
        void UpdatePosition(float elapsedTimeSinceLastFrame) noexcept;
        
        // Use this function in cursor position callback
        void UpdateOrientation(float xOffset, float yOffset) noexcept;
    };
}

#endif // __CAMERA_H__
