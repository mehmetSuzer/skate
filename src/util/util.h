
#ifndef __UTIL_H__
#define __UTIL_H__

#include "exception.h"
#include "glad.h"
#include "glm.hpp"

namespace skate 
{
    // Contains utility variables and functions
    namespace util 
    {
        extern const std::string dataDir;
        extern const std::string modelsDir;
        extern const std::string texturesDir;

        extern const glm::vec4 backgroundColor;

        extern GLsizei windowWidth;
        extern GLsizei windowHeight;
        extern float aspectRatio;

        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept;
    }
}

#endif // __UTIL_H__
