
#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <camera.h>
#include <GLFW/glfw3.h>

class InputHandler {
private:
    static InputHandler instance;

    float cursorPosSensitivity = M_PIf / 1800.0f;
    float scrollSensitivity = M_PIf / 180.0f;

public:
    static InputHandler& Instance(void) {
        return instance;
    }

    void Initialize(GLFWwindow* window);

    float GetCursorPosSensitivity(void) const {
        return cursorPosSensitivity;
    }

    float GetScrollSensitivity(void) const {
        return scrollSensitivity;
    }

    void ActivateInputs(GLFWwindow *window);
    void DeactivateInputs(GLFWwindow* window);
};

#endif // __INPUT_HANDLER_H__
