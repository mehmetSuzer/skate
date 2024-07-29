
#ifndef __UTIL_H__
#define __UTIL_H__

#include <fstream>
#include <sstream>
#include "exception.h"
#include "glad.h"
#include "glm.hpp"

namespace skate 
{
    // Contains utility variables and functions
    namespace util 
    {
        enum ShaderProgramType 
        {
            VERTEX_SHADER_PROGRAM = 0,
            FRAGMENT_SHADER_PROGRAM,
        };

        enum ShaderType 
        {
            COLOR_SHADER = 0,
            MATERIAL_SHADER,
            TEXTURE_SHADER,
            LIGHT_SHADER,
        };

        extern const std::string dataDir;
        extern const std::string modelsDir;
        extern const std::string texturesDir;

        extern const glm::vec4 backgroundColor;

        extern GLsizei windowWidth;
        extern GLsizei windowHeight;
        extern float aspectRatio;

        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept;
        std::string ReadShaderSource(const std::string& filename);
        const std::string GetShaderProgramPath(enum ShaderProgramType shaderProgram, enum ShaderType shader) noexcept;
    }
}

#endif // __UTIL_H__
