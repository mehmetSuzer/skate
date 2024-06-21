
#include "input_handler.h"

InputHandler InputHandler::instance;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Common::Instance().SetWindowWidthAndHeight(width, height);
    Camera::Instance().UpdatePerspective();
}

void activeKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_1:
            InputHandler::Instance().DeactivateInputs(window);
            break;
        case GLFW_KEY_W:
            Camera::Instance().SetForwardDirection(AXIS_POSITIVE);
            break;
        case GLFW_KEY_S:
            Camera::Instance().SetForwardDirection(AXIS_NEGATIVE);
            break;
        case GLFW_KEY_D:
            Camera::Instance().SetRightDirection(AXIS_POSITIVE);
            break;
        case GLFW_KEY_A:
            Camera::Instance().SetRightDirection(AXIS_NEGATIVE);
            break;
        case GLFW_KEY_SPACE:
            Camera::Instance().SetUpDirection(AXIS_POSITIVE);
            break;
        case GLFW_KEY_LEFT_CONTROL:
            Camera::Instance().SetUpDirection(AXIS_NEGATIVE);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            Camera::Instance().SetHighSpeed();
            break;
        default:
            break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            break;
        case GLFW_KEY_W:
        case GLFW_KEY_S:
            Camera::Instance().SetForwardDirection(AXIS_NONE);
            break;
        case GLFW_KEY_D:
        case GLFW_KEY_A:
            Camera::Instance().SetRightDirection(AXIS_NONE);
            break;
        case GLFW_KEY_SPACE:
        case GLFW_KEY_LEFT_CONTROL:
            Camera::Instance().SetUpDirection(AXIS_NONE);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            Camera::Instance().SetLowSpeed();
            break;
        default:
            break;
        }
    }
}

void deactiveKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key)
        {
        case GLFW_KEY_1:
            InputHandler::Instance().ActivateInputs(window);
            break;
        default:
            break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key)
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

void InputHandler::Initialize(GLFWwindow* window) {
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
