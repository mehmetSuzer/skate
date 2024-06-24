
#include "common.h"

Common Common::instance;

std::string Common::ReadFile(const char* filename) const {
    std::ifstream in(filename, std::ios::binary);

    #ifdef __COMPILE_ERROR_HANDLERS__
    if (!in) {
        std::string errorMessage = "File " + std::string(filename) + " couldn't be found!";
        throw Error(errorMessage);
    }
    #endif 
    
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

const std::string Common::GetShaderProgramPath(enum ShadingType shading, enum ShaderType shader, enum VertexType vertex) const {
    const std::string& shadingPath = (shading == FLAT_SHADING)    ? flatShadingPath : 
                                     (shading == GOURAUD_SHADING) ? gouraudShadingPath : 
                                                                    phongShadingPath;

    const std::string& shaderPath = (shader == VERTEX_SHADER) ? vertexShaderPath : 
                                                                fragmentShaderPath;

    const std::string& vertexPath = (vertex == BASIC_VERTEX)    ? basicVertexGLSL : 
                                    (vertex == COLOR_VERTEX)    ? colorVertexGLSL : 
                                    (vertex == TEXTURE_VERTEX)  ? textureVertexGLSL :
                                    (vertex == MATERIAL_VERTEX) ? materialVertexGLSL :
                                                                  lightingMapVertexGLSL;

    return shadingPath + shaderPath + vertexPath;
}
