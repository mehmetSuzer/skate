
#include "util.h"

namespace skate 
{
    namespace util 
    {
        const std::string dataDir = "data/";
        const std::string modelsDir = dataDir + "models/";
        const std::string texturesDir = dataDir + "textures/";

        const glm::vec4 backgroundColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);

        GLsizei windowWidth = 1000;
        GLsizei windowHeight = 800;
        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        
        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept 
        {
            windowWidth = windowWidth_;
            windowHeight = windowHeight_;
            aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        }
    }
}
