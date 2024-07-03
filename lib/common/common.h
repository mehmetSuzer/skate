
#ifndef __COMMON_H__
#define __COMMON_H__

#include <fstream>
#include "config.h"
#include "exception.h"
#include "glad.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

enum ShadingType {
    GOURAUD_SHADING = 0,
    PHONG_SHADING,
};

enum ShaderType {
    VERTEX_SHADER = 0,
    FRAGMENT_SHADER,
};

enum VertexType {
    COLOR_VERTEX = 0,
    MATERIAL_VERTEX,
    TEXTURE_VERTEX,
};

class Common {
private:
    static Common instance;

    const std::string glslPath = "glsl/";
    const std::string gouraudShadingPath = glslPath + "gouraud/";
    const std::string phongShadingPath = glslPath + "phong/";

    const std::string vertexShaderPath = "vertex/";
    const std::string fragmentShaderPath = "fragment/";

    const std::string glslFileExtension = ".glsl";
    const std::string colorVertexGLSL = "color" + glslFileExtension;
    const std::string materialVertexGLSL = "material" + glslFileExtension;
    const std::string textureVertexGLSL = "texture" + glslFileExtension;

    const std::string dataPath = "data/";
    const std::string modelsPath = dataPath + "models/";
    const std::string texturesPath = dataPath + "textures/";

    const glm::vec4 backgroundColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);

    GLsizei windowWidth = 1000;
    GLsizei windowHeight = 800;
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

    float secondsPerPhysicsUpdate = 1.0f / 50.0f;

    Common() {}
    
public:
    static Common& Instance(void) {
        return instance;
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

    std::string ReadFile(const char* filePath) const;
    const std::string GetShaderProgramPath(enum ShadingType shading, enum ShaderType shader, enum VertexType vertex) const;
};

#endif // __COMMON_H__
