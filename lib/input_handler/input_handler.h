
#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <camera.h>
#include <GLFW/glfw3.h>

typedef enum {
    UNKNOWN_BUTTON = 0,
    ESCAPE_BUTTON,
    INPUT_ACTIVATION_BUTTON,
    FORWARD_BUTTON,
    BACKWARD_BUTTON,
    RIGHT_BUTTON,
    LEFT_BUTTON,
    UP_BUTTON,
    DOWN_BUTTON,
    SPEED_UP_BUTTON,
} Button;

class InputHandler {
private:
    static InputHandler instance;
    bool initialized = false;

    float cursorPosSensitivity = M_PIf / 1800.0f;
    float scrollSensitivity = M_PIf / 180.0f;

    static const uint32_t buttonMapSize = GLFW_KEY_LAST+1;
    uint8_t buttonMap[buttonMapSize];

public:
    static InputHandler& Instance(void) {
        return instance;
    }

    float GetCursorPosSensitivity(void) const {
        return cursorPosSensitivity;
    }

    void SetCursorPosSensitivity(float sensitivity) {
        cursorPosSensitivity = sensitivity;
    }

    float GetScrollSensitivity(void) const {
        return scrollSensitivity;
    }

    void SetScrollSensitivity(float sensitivity) {
        scrollSensitivity = sensitivity;
    }

    uint8_t GetButton(GLuint key) const {
        return buttonMap[key];
    }

    void SetButton(GLuint key, Button button);
    void Initialize(GLFWwindow* window);
    void ActivateInputs(GLFWwindow *window);
    void DeactivateInputs(GLFWwindow* window);
};

#endif // __INPUT_HANDLER_H__
