
#include "camera.h"

namespace skate 
{
    Camera::Camera(const glm::vec3& position, float near_, float far_, float FOVRadian_, float minFOVRadian_, float maxFOVRadian_)
        : near(near_), far(far_), FOVRadian(FOVRadian_), minFOVRadian(minFOVRadian_), maxFOVRadian(maxFOVRadian_)
    {
        transform.SetPosition(position);
        UpdateView();
        UpdateProjection();
    }

    void Camera::UpdateFOVRadian(float deltaFOVRadian) noexcept 
    {
        FOVRadian += deltaFOVRadian;
        if (FOVRadian < minFOVRadian) 
            FOVRadian = minFOVRadian;
        else if (FOVRadian > maxFOVRadian)
            FOVRadian = maxFOVRadian;

        UpdateProjection();
    }

    void Camera::UpdatePosition(float elapsedTimeSinceLastFrame) noexcept 
    {
        glm::vec3 velocityDirection = glm::vec3(0.0f);
        uint32_t activeDirection = 0;

        if (direction.forward == AXIS_POSITIVE) 
        {
            velocityDirection += transform.GetForward();
            activeDirection++;
        } 
        else if (direction.forward == AXIS_NEGATIVE) 
        {
            velocityDirection -= transform.GetForward();
            activeDirection++;
        }

        if (direction.right == AXIS_POSITIVE) 
        {
            velocityDirection += transform.GetRight();
            activeDirection++;
        } 
        else if (direction.right == AXIS_NEGATIVE) 
        {
            velocityDirection -= transform.GetRight();
            activeDirection++;
        }

        if (direction.up == AXIS_POSITIVE) 
        {
            velocityDirection += Transform::WorldUp;
            activeDirection++;
        } 
        else if (direction.up == AXIS_NEGATIVE) 
        {
            velocityDirection -= Transform::WorldUp;
            activeDirection++;
        }

        if (activeDirection != 0)
        {
            transform.Translate(velocityDirection * (elapsedTimeSinceLastFrame * speed / glm::sqrt(static_cast<float>(activeDirection))));
            UpdateView();
        }
    }

    void Camera::UpdateOrientation(float xOffset, float yOffset) noexcept 
    {
        // prevent camera to roll vertically
        float cosAngle = glm::dot(transform.GetForward(), Transform::WorldUp);
        if (cosAngle + yOffset > maxCosAngleBetweenForwardAndWorldUp)
            yOffset = maxCosAngleBetweenForwardAndWorldUp - cosAngle;
        else if (cosAngle + yOffset < -maxCosAngleBetweenForwardAndWorldUp)
            yOffset = -(maxCosAngleBetweenForwardAndWorldUp + cosAngle);
        
        const glm::quat yQuat = glm::angleAxis(yOffset, transform.GetRight());
        const glm::quat xQuat = glm::angleAxis(-xOffset, Transform::WorldUp);
        transform.Rotate(xQuat * yQuat);
        UpdateView();
    }
}
