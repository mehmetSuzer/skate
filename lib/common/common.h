
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

    Common() {}
    
public:
    inline static Common& Instance(void) {
        return instance;
    }

    inline const std::string& GetModelsPath(void) const {
        return modelsPath;
    }

    inline const std::string& GetTexturesPath(void) const {
        return texturesPath;
    }

    inline const glm::vec4& GetBackgroundColor(void) const {
        return backgroundColor;
    }

    inline GLsizei GetWindowWidth(void) const {
        return windowWidth;
    }

    inline GLsizei GetWindowHeight(void) const {
        return windowHeight;
    }

    inline float GetAspectRatio(void) const {
        return aspectRatio;
    }

    inline void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) {
        windowWidth = windowWidth_;
        windowHeight = windowHeight_;
        aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    }

    std::string ReadFile(const std::string& filePath) const;
    const std::string GetShaderProgramPath(enum ShadingType shading, enum ShaderType shader, enum VertexType vertex) const;
};

#endif // __COMMON_H__
