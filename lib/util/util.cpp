
#include "util.h"

namespace util {

    const std::string glslPath = "glsl/";
    const std::string vertexShaderPath = glslPath + "vertex/";
    const std::string fragmentShaderPath = glslPath + "fragment/";

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
    
    void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept {
        windowWidth = windowWidth_;
        windowHeight = windowHeight_;
        aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    }

    std::string ReadFile(const std::string& filename) {
        std::ifstream in = std::ifstream(filename, std::ios::binary);

        if (!in) {
            std::string message = "File " + filename + " couldn't be found!";
            throw Exception(message);
        }
        
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }

    const std::string GetShaderProgramPath(enum ShaderType shader, enum VertexType vertex) noexcept {
        const std::string& shaderPath = (shader == VERTEX_SHADER) ? vertexShaderPath : 
                                                                    fragmentShaderPath;

        const std::string& filename = (vertex == COLOR_VERTEX)    ? colorVertexGLSL : 
                                      (vertex == MATERIAL_VERTEX) ? materialVertexGLSL :
                                                                    textureVertexGLSL;
        return shaderPath + filename;
    }
}
