
#include "camera.h"

Camera Camera::instance;

void Camera::UpdateVectors(void) {
    forward = glm::vec3(
        cosf(yaw) * cosf(pitch),    // x
        sinf(pitch),                // y
        sinf(yaw) * cosf(pitch)     // z
    );
    up = glm::vec3(sinf(roll), cosf(roll), 0.0f);
    right = glm::normalize(glm::cross(forward, up));
}

void Camera::Initialize(void) {
    if (initialized) {
        return;
    }
    initialized = true;

    UpdateVectors();
    UpdateView();
    UpdatePerspective();
}

void Camera::UpdateFOVradian(float deltaFOVradian) {
    FOVradian += deltaFOVradian;
    if (FOVradian < minFOVradian) {
        FOVradian = minFOVradian;
    } else if (FOVradian > maxFOVradian) {
        FOVradian = maxFOVradian;
    }
    UpdatePerspective();
}

void Camera::UpdatePosition(float elapsedTimeSinceLastFrame) {
    glm::vec3 velocityDirection = glm::vec3(0.0f, 0.0f, 0.0f);

    if (direction.forward == AXIS_POSITIVE) {
        velocityDirection += forward;
    } else if (direction.forward == AXIS_NEGATIVE) {
        velocityDirection -= forward;
    }

    if (direction.right == AXIS_POSITIVE) {
        velocityDirection += right;
    } else if (direction.right == AXIS_NEGATIVE) {
        velocityDirection -= right;
    }

    if (direction.up == AXIS_POSITIVE) {
        velocityDirection += up;
    } else if (direction.up == AXIS_NEGATIVE) {
        velocityDirection -= up;
    }

    float length = glm::length(velocityDirection);
    if (glm::epsilonNotEqual(length, 0.0f, 1E-6f)) {
        position += velocityDirection * (elapsedTimeSinceLastFrame * speed / length);
        UpdateView();
    }
}

void Camera::UpdateOrientation(float xOffset, float yOffset) {
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
