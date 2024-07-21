
#ifndef __UTIL_H__
#define __UTIL_H__

#include <fstream>
#include "exception.h"
#include "glad.h"
#include "glm.hpp"

namespace skate 
{
    namespace util 
    {
        enum ShaderType 
        {
            VERTEX_SHADER = 0,
            FRAGMENT_SHADER,
        };

        enum VertexType 
        {
            COLOR_VERTEX = 0,
            MATERIAL_VERTEX,
            TEXTURE_VERTEX,
        };

        extern const std::string glslPath;
        extern const std::string vertexShaderPath;
        extern const std::string fragmentShaderPath;

        extern const std::string glslFileExtension;
        extern const std::string colorVertexGLSL;
        extern const std::string materialVertexGLSL;
        extern const std::string textureVertexGLSL;

        extern const std::string dataPath;
        extern const std::string modelsPath;
        extern const std::string texturesPath;

        extern const glm::vec4 backgroundColor;

        extern GLsizei windowWidth;
        extern GLsizei windowHeight;
        extern float aspectRatio;

        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept;
        std::string ReadFile(const std::string& filePath);
        const std::string GetShaderProgramPath(enum ShaderType shader, enum VertexType vertex) noexcept;
    }
}

#endif // __UTIL_H__
