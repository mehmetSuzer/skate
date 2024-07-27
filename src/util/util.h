
#ifndef __UTIL_H__
#define __UTIL_H__

#include <fstream>
#include <sstream>
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

        extern const std::string dataDir;
        extern const std::string modelsDir;
        extern const std::string texturesDir;

        extern const glm::vec4 backgroundColor;

        extern GLsizei windowWidth;
        extern GLsizei windowHeight;
        extern float aspectRatio;

        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept;
        std::string ReadShaderSource(const std::string& filename);
        const std::string GetShaderProgramPath(enum ShaderType shader, enum VertexType vertex) noexcept;
    }
}

#endif // __UTIL_H__
