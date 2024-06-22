
#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <glad.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Common {
private:
    static Common instance;

    std::string glslPath = "glsl/";
    std::string modelsPath = "data/models/";
    std::string texturesPath = "data/textures/";

    glm::vec4 backgroundColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);

    GLsizei windowWidth = 1000;
    GLsizei windowHeight = 800;
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    float secondsPerPhysicsUpdate = 1.0f / 50.0f;

    Common() {}
    
public:
    static Common& Instance(void) {
        return instance;
    }

    const std::string& GetGLSLPath(void) const {
        return glslPath;
    }

    const std::string& GetModelsPath(void) const {
        return modelsPath;
    }

    const std::string& GetTexturesPath(void) const {
        return texturesPath;
    }

    const glm::vec4& GetBackgroundColor(void) const {
        return backgroundColor;
    }

    GLsizei GetWindowWidth(void) const {
        return windowWidth;
    }

    GLsizei GetWindowHeight(void) const {
        return windowHeight;
    }

    float GetAspectRatio(void) const {
        return aspectRatio;
    }

    void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) {
        windowWidth = windowWidth_;
        windowHeight = windowHeight_;
        aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    }

    float GetSecondsPerPhysicsUpdate(void) const {
        return secondsPerPhysicsUpdate;
    }

    float RGB2Gray(float red, float green, float blue) const {
        return 0.299f * red + 0.587f * green + 0.114f * blue;
    }
};

#endif // __COMMON_H__
