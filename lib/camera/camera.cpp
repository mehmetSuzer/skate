
#include "camera.h"

Camera Camera::instance;

void Camera::UpdateVectors(void) {
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

void Camera::UpdateFlashLight(void) {
    flashLight.SetPosition(position);
    flashLight.SetDirection(forward);
}

void Camera::Initialize(void) {
    if (initialized) {
        return;
    }
    initialized = true;

    UpdateVectors();
    UpdateView();
    UpdateProjection();
    UpdateFlashLight();
}

void Camera::UpdateFOVradian(float deltaFOVradian) {
    FOVradian += deltaFOVradian;
    if (FOVradian < minFOVradian) {
        FOVradian = minFOVradian;
    } else if (FOVradian > maxFOVradian) {
        FOVradian = maxFOVradian;
    }
    UpdateProjection();
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
        UpdateFlashLight();
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
    UpdateFlashLight();
}
