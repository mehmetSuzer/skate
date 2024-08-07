
#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include "glad.h"

namespace skate 
{
    // Contains utility variables and functions
    namespace util 
    {
        extern const std::string dataDir;
        extern const std::string modelsDir;
        extern const std::string texturesDir;

        extern GLsizei windowWidth;
        extern GLsizei windowHeight;
        extern float aspectRatio;

        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept;
    }
}

#endif // __UTIL_H__
