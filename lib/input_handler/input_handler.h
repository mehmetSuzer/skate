
#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <camera.h>
#include <GLFW/glfw3.h>

class InputHandler {
private:
    static InputHandler instance;

public:
    static InputHandler& Instance(void) {
        return instance;
    }

    void Initialize(GLFWwindow* window);

    void ActivateInputs(GLFWwindow *window);
    void DeactivateInputs(GLFWwindow* window);
};

#endif // __INPUT_HANDLER_H__
