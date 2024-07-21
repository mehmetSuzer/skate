
#include "camera.h"

Camera Camera::instance;

void Camera::UpdateVectors(void) noexcept {
    const float sinYaw = glm::sin(yaw);
    const float cosYaw = glm::cos(yaw);
    const float sinPitch = glm::sin(pitch);
    const float cosPitch =  glm::cos(pitch);

    forward = glm::vec3(
        cosYaw * cosPitch,  // x
        sinPitch,           // y
        sinYaw * cosPitch   // z
    );
    right = glm::normalize(glm::cross(forward, up));
}

void Camera::Initialize(void) noexcept {
    if (initialized) {
        return;
    }
    initialized = true;

    UpdateVectors();
    UpdateView();
    UpdateProjection();
}

void Camera::UpdateFOVradian(float deltaFOVradian) noexcept {
    FOVradian += deltaFOVradian;
    if (FOVradian < minFOVradian) {
        FOVradian = minFOVradian;
    } else if (FOVradian > maxFOVradian) {
        FOVradian = maxFOVradian;
    }
    UpdateProjection();
}

void Camera::UpdatePosition(float elapsedTimeSinceLastFrame) noexcept {
    glm::vec3 velocityDirection = glm::vec3(0.0f, 0.0f, 0.0f);
    uint32_t activeDirection = 0;

    if (direction.forward == AXIS_POSITIVE) {
        velocityDirection += forward;
        activeDirection++;
    } else if (direction.forward == AXIS_NEGATIVE) {
        velocityDirection -= forward;
        activeDirection++;
    }

    if (direction.right == AXIS_POSITIVE) {
        velocityDirection += right;
        activeDirection++;
    } else if (direction.right == AXIS_NEGATIVE) {
        velocityDirection -= right;
        activeDirection++;
    }

    if (direction.up == AXIS_POSITIVE) {
        velocityDirection += up;
        activeDirection++;
    } else if (direction.up == AXIS_NEGATIVE) {
        velocityDirection -= up;
        activeDirection++;
    }

    if (activeDirection == 0) {
        return;
    } else if (activeDirection == 1) {
        position += velocityDirection * (elapsedTimeSinceLastFrame * speed);
    } else {
        float length = glm::length(velocityDirection);
        position += velocityDirection * (elapsedTimeSinceLastFrame * speed / length);
    }

    UpdateView();
}

void Camera::UpdateOrientation(float xOffset, float yOffset) noexcept {
    yaw   += xOffset;
    pitch += yOffset;

    // Prevent the camera from looking at too up or too down
    if (pitch > maxPitch) {
		pitch = maxPitch;
	} else if (pitch < -maxPitch) {
		pitch = -maxPitch;
	}

	UpdateVectors();
    UpdateView();
}
