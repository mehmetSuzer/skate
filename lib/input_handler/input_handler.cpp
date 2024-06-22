
#include "input_handler.h"

InputHandler InputHandler::instance;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Common::Instance().SetWindowWidthAndHeight(width, height);
    Camera::Instance().UpdateProjection();
}

void activeKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const uint8_t button = InputHandler::Instance().GetButton(key);
    if (action == GLFW_PRESS) {
        switch (button)
        {
        case ESCAPE_BUTTON:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case INPUT_ACTIVATION_BUTTON:
            InputHandler::Instance().DeactivateInputs(window);
            break;
        case FORWARD_BUTTON:
            Camera::Instance().SetForwardDirection(AXIS_POSITIVE);
            break;
        case BACKWARD_BUTTON:
            Camera::Instance().SetForwardDirection(AXIS_NEGATIVE);
            break;
        case RIGHT_BUTTON:
            Camera::Instance().SetRightDirection(AXIS_POSITIVE);
            break;
        case LEFT_BUTTON:
            Camera::Instance().SetRightDirection(AXIS_NEGATIVE);
            break;
        case UP_BUTTON:
            Camera::Instance().SetUpDirection(AXIS_POSITIVE);
            break;
        case DOWN_BUTTON:
            Camera::Instance().SetUpDirection(AXIS_NEGATIVE);
            break;
        case SPEED_UP_BUTTON:
            Camera::Instance().SetHighSpeed();
            break;
        default:
            break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (button)
        {
        case ESCAPE_BUTTON:
            break;
        case FORWARD_BUTTON:
        case BACKWARD_BUTTON:
            Camera::Instance().SetForwardDirection(AXIS_NONE);
            break;
        case RIGHT_BUTTON:
        case LEFT_BUTTON:
            Camera::Instance().SetRightDirection(AXIS_NONE);
            break;
        case UP_BUTTON:
        case DOWN_BUTTON:
            Camera::Instance().SetUpDirection(AXIS_NONE);
            break;
        case SPEED_UP_BUTTON:
            Camera::Instance().SetLowSpeed();
            break;
        default:
            break;
        }
    }
}

void deactiveKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const uint8_t button = InputHandler::Instance().GetButton(key);
    if (action == GLFW_PRESS) {
        switch (button)
        {
        case INPUT_ACTIVATION_BUTTON:
            InputHandler::Instance().ActivateInputs(window);
            break;
        default:
            break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (button)
        {
        default:
            break;
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    // Last positions from the last mouse callback
	static double lastX = Common::Instance().GetWindowWidth() / 2.0; 
	static double lastY = Common::Instance().GetWindowHeight() / 2.0;
    static bool firstMouse = true;

    // Prevent mouse to overshoot the scene in the first mouse callback
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
  
    // Update the last positions
    float xOffset = static_cast<float>(xPos - lastX) * InputHandler::Instance().GetCursorPosSensitivity();
    float yOffset = static_cast<float>(lastY - yPos) * InputHandler::Instance().GetCursorPosSensitivity(); 
    lastX = xPos;
    lastY = yPos;

    Camera::Instance().UpdateOrientation(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    float deltaFOVradian = yOffset * InputHandler::Instance().GetScrollSensitivity();
    Camera::Instance().UpdateFOVradian(deltaFOVradian);
}

void InputHandler::SetButton(GLuint key, Button button) {
    for (uint32_t i = 0; i < buttonMapSize; i++) {
        if (buttonMap[i] == button) {
            buttonMap[i] = UNKNOWN_BUTTON;
            break;
        }
    }
    buttonMap[key] = button;
}

void InputHandler::Initialize(GLFWwindow* window) {
    if (initialized) {
        return;
    }
    initialized = true;

    // Clear all buttons
    for (uint32_t i = 0; i < buttonMapSize; i++) {
        buttonMap[i] = UNKNOWN_BUTTON;
    }

    // Default buttons
    buttonMap[GLFW_KEY_ESCAPE] = ESCAPE_BUTTON;
    buttonMap[GLFW_KEY_1] = INPUT_ACTIVATION_BUTTON;
    buttonMap[GLFW_KEY_W] = FORWARD_BUTTON;
    buttonMap[GLFW_KEY_S] = BACKWARD_BUTTON;
    buttonMap[GLFW_KEY_D] = RIGHT_BUTTON;
    buttonMap[GLFW_KEY_A] = LEFT_BUTTON;
    buttonMap[GLFW_KEY_SPACE] = UP_BUTTON;
    buttonMap[GLFW_KEY_LEFT_CONTROL] = DOWN_BUTTON;
    buttonMap[GLFW_KEY_LEFT_SHIFT] = SPEED_UP_BUTTON;

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    ActivateInputs(window);
}

void InputHandler::ActivateInputs(GLFWwindow *window) {
    glfwSetCursorPos(window, (Common::Instance().GetWindowWidth() / 2.0), (Common::Instance().GetWindowHeight() / 2.0));
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, activeKeyCallback);
    glfwSetScrollCallback(window, scrollCallback);
}
    
void InputHandler::DeactivateInputs(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, NULL);
    glfwSetKeyCallback(window, deactiveKeyCallback);
    glfwSetScrollCallback(window, NULL);
}
