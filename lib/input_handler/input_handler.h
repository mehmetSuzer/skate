
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
    inline static InputHandler& Instance(void) noexcept {
        return instance;
    }

    inline float GetCursorPosSensitivity(void) const noexcept {
        return cursorPosSensitivity;
    }

    inline void SetCursorPosSensitivity(float sensitivity) noexcept {
        cursorPosSensitivity = sensitivity;
    }

    inline float GetScrollSensitivity(void) const noexcept {
        return scrollSensitivity;
    }

    inline void SetScrollSensitivity(float sensitivity) noexcept {
        scrollSensitivity = sensitivity;
    }

    inline bool GetFirstMouse(void) const noexcept {
        return firstMouse;
    }

    inline void SetFirstMouse(bool boolean) noexcept {
        firstMouse = boolean;
    }

    inline enum Button GetButton(GLuint key) const noexcept {
        return buttonMap[key];
    }

    void SetButton(GLuint key, enum Button button) noexcept;
    void Initialize(GLFWwindow* window) noexcept;
    void ActivateInputs(GLFWwindow *window) noexcept;
    void DeactivateInputs(GLFWwindow* window) noexcept;
};

#endif // __INPUT_HANDLER_H__
