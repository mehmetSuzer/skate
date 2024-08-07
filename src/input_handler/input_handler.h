
#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include "config.h"
#include "camera.h"

namespace skate 
{
    // Singleton input handler which handles the mouse and the keyboard inputs
    class InputHandler 
    {
    public:
        enum Button
        {
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
        
        static InputHandler instance;
        bool initialized = false;

        float cursorPosSensitivity = M_PIf / 1800.0f;
        float scrollSensitivity = M_PIf / 180.0f;
        bool firstMouse = true;

        static const uint32_t buttonMapSize = GLFW_KEY_LAST+1;
        Button buttonMap[buttonMapSize];

        Camera* selectedCamera = NULL;

    public:
        inline static InputHandler& Instance(void) noexcept 
        {
            return instance;
        }

        inline Camera* GetSelectedCamera(void) const noexcept
        {
            return selectedCamera;
        }

        inline void SelectCamera(Camera* camera) noexcept
        {
            selectedCamera = camera;
        }

        inline float GetCursorPosSensitivity(void) const noexcept 
        {
            return cursorPosSensitivity;
        }

        inline void SetCursorPosSensitivity(float sensitivity) noexcept 
        {
            cursorPosSensitivity = sensitivity;
        }

        inline float GetScrollSensitivity(void) const noexcept 
        {
            return scrollSensitivity;
        }

        inline void SetScrollSensitivity(float sensitivity) noexcept 
        {
            scrollSensitivity = sensitivity;
        }

        inline bool IsFirstMouse(void) const noexcept 
        {
            return firstMouse;
        }

        inline void ClearFirstMouse(void) noexcept 
        {
            firstMouse = false;
        }

        inline Button GetButton(GLuint key) const noexcept 
        {
            return buttonMap[key];
        }

        void SetButton(GLuint key, Button button) noexcept;
        void Initialize(GLFWwindow* window) noexcept;
        void ActivateInputs(GLFWwindow *window) noexcept;
        void DeactivateInputs(GLFWwindow* window) noexcept;
    };
}

#endif // __INPUT_HANDLER_H__
