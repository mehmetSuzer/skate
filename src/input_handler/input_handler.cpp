
#include "input_handler.h"

namespace skate 
{
    // ------------------------------------------ CALLBACKS ------------------------------------------ //

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept 
    {
        glViewport(0, 0, width, height);
        Camera::SetWindowWidthAndHeight(width, height);
        Camera* selectedCamera = InputHandler::Instance().GetSelectedCamera();
        if (selectedCamera != NULL)
            selectedCamera->UpdateProjection();
    }

    static void activeKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) noexcept 
    {
        Camera* selectedCamera = InputHandler::Instance().GetSelectedCamera();
        const InputHandler::Button button = InputHandler::Instance().GetButton(key);

        if (selectedCamera == NULL && button != InputHandler::ESCAPE_BUTTON && button != InputHandler::INPUT_ACTIVATION_BUTTON)
            return;

        if (action == GLFW_PRESS) 
        {
            switch (button)
            {
            case InputHandler::ESCAPE_BUTTON:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case InputHandler::INPUT_ACTIVATION_BUTTON:
                InputHandler::Instance().DeactivateInputs(window);
                break;
            case InputHandler::FORWARD_BUTTON:
                selectedCamera->SetForwardDirection(Camera::AXIS_POSITIVE);
                break;
            case InputHandler::BACKWARD_BUTTON:
                selectedCamera->SetForwardDirection(Camera::AXIS_NEGATIVE);
                break;
            case InputHandler::RIGHT_BUTTON:
                selectedCamera->SetRightDirection(Camera::AXIS_POSITIVE);
                break;
            case InputHandler::LEFT_BUTTON:
                selectedCamera->SetRightDirection(Camera::AXIS_NEGATIVE);
                break;
            case InputHandler::UP_BUTTON:
                selectedCamera->SetUpDirection(Camera::AXIS_POSITIVE);
                break;
            case InputHandler::DOWN_BUTTON:
                selectedCamera->SetUpDirection(Camera::AXIS_NEGATIVE);
                break;
            case InputHandler::SPEED_UP_BUTTON:
                selectedCamera->SetHighSpeed();
                break;
            default:
                break;
            }
        } 
        else if (action == GLFW_RELEASE) 
        {
            switch (button)
            {
            case InputHandler::ESCAPE_BUTTON:
                break;
            case InputHandler::FORWARD_BUTTON:
            case InputHandler::BACKWARD_BUTTON:
                selectedCamera->SetForwardDirection(Camera::AXIS_NONE);
                break;
            case InputHandler::RIGHT_BUTTON:
            case InputHandler::LEFT_BUTTON:
                selectedCamera->SetRightDirection(Camera::AXIS_NONE);
                break;
            case InputHandler::UP_BUTTON:
            case InputHandler::DOWN_BUTTON:
                selectedCamera->SetUpDirection(Camera::AXIS_NONE);
                break;
            case InputHandler::SPEED_UP_BUTTON:
                selectedCamera->SetLowSpeed();
                break;
            default:
                break;
            }
        }
    }

    static void deactiveKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) noexcept 
    {
        const InputHandler::Button button = InputHandler::Instance().GetButton(key);
        if (action == GLFW_PRESS) 
        {
            switch (button)
            {
            case InputHandler::INPUT_ACTIVATION_BUTTON:
                InputHandler::Instance().ActivateInputs(window);
                break;
            default:
                break;
            }
        }
    }

    static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) noexcept 
    {
        // Last positions from the last mouse callback
        static float lastX = Camera::windowWidth / 2.0f; 
        static float lastY = Camera::windowWidth / 2.0f;

        float xPosf = static_cast<float>(xPos);
        float yPosf = static_cast<float>(yPos);

        // Prevent mouse to overshoot the scene in the first mouse callback
        if (InputHandler::Instance().IsFirstMouse()) 
        {
            lastX = xPosf;
            lastY = yPosf;
            InputHandler::Instance().ClearFirstMouse();
        }
    
        // Update the last positions
        const float xOffset = (xPosf - lastX) * InputHandler::Instance().GetCursorPosSensitivity();
        const float yOffset = (lastY - yPosf) * InputHandler::Instance().GetCursorPosSensitivity(); 
        lastX = xPosf;
        lastY = yPosf;

        Camera* selectedCamera = InputHandler::Instance().GetSelectedCamera();
        if (selectedCamera != NULL)    
            selectedCamera->UpdateOrientation(xOffset, yOffset);
    }

    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) noexcept 
    {
        const float deltaFOVRadian = yOffset * InputHandler::Instance().GetScrollSensitivity();
        Camera* selectedCamera = InputHandler::Instance().GetSelectedCamera();
        if (selectedCamera != NULL)    
            selectedCamera->UpdateFOVRadian(deltaFOVRadian);
    }

    // ---------------------------------------------------------------------------------------------- //

    InputHandler InputHandler::instance;

    void InputHandler::SetButton(GLuint key, Button button) noexcept 
    {
        uint32_t index = 0;
        while (index < buttonMapSize && buttonMap[index] != button) 
            index++;

        if (index < buttonMapSize)
            buttonMap[index] = UNKNOWN_BUTTON;

        buttonMap[key] = button;
    }

    void InputHandler::Initialize(GLFWwindow* window) noexcept {
        if (initialized) 
            return;
        initialized = true;

        // Clear all buttons
        for (uint32_t i = 0; i < buttonMapSize; i++) 
            buttonMap[i] = UNKNOWN_BUTTON;

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

    void InputHandler::ActivateInputs(GLFWwindow *window) noexcept 
    {
        glfwSetCursorPos(window, Camera::windowWidth / 2.0, Camera::windowHeight / 2.0);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, cursorPosCallback);
        glfwSetKeyCallback(window, activeKeyCallback);
        glfwSetScrollCallback(window, scrollCallback);
        firstMouse = true;
    }
        
    void InputHandler::DeactivateInputs(GLFWwindow* window) noexcept 
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, NULL);
        glfwSetKeyCallback(window, deactiveKeyCallback);
        glfwSetScrollCallback(window, NULL);
    }
}
