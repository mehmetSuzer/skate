
#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include "camera.h"
#include <GLFW/glfw3.h>

enum Button : uint8_t {
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
};

class InputHandler {
private:
    static InputHandler instance;
    bool initialized = false;

    float cursorPosSensitivity = M_PIf / 1800.0f;
    float scrollSensitivity = M_PIf / 180.0f;
    bool firstMouse = true;

    static const uint32_t buttonMapSize = GLFW_KEY_LAST+1;
    enum Button buttonMap[buttonMapSize];

public:
    inline static InputHandler& Instance(void) {
        return instance;
    }

    inline float GetCursorPosSensitivity(void) const {
        return cursorPosSensitivity;
    }

    inline void SetCursorPosSensitivity(float sensitivity) {
        cursorPosSensitivity = sensitivity;
    }

    inline float GetScrollSensitivity(void) const {
        return scrollSensitivity;
    }

    inline void SetScrollSensitivity(float sensitivity) {
        scrollSensitivity = sensitivity;
    }

    inline bool GetFirstMouse(void) const {
        return firstMouse;
    }

    inline void SetFirstMouse(bool boolean) {
        firstMouse = boolean;
    }

    inline enum Button GetButton(GLuint key) const {
        return buttonMap[key];
    }

    void SetButton(GLuint key, enum Button button);
    void Initialize(GLFWwindow* window);
    void ActivateInputs(GLFWwindow *window);
    void DeactivateInputs(GLFWwindow* window);
};

#endif // __INPUT_HANDLER_H__
