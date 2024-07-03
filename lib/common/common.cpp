
#include "common.h"

Common Common::instance;

std::string Common::ReadFile(const std::string& filename) const {
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

const std::string Common::GetShaderProgramPath(enum ShadingType shading, enum ShaderType shader, enum VertexType vertex) const {
    const std::string& shadingPath = (shading == GOURAUD_SHADING) ? gouraudShadingPath : 
                                                                    phongShadingPath;

    const std::string& shaderPath = (shader == VERTEX_SHADER) ? vertexShaderPath : 
                                                                fragmentShaderPath;

    const std::string& vertexPath = (vertex == COLOR_VERTEX)    ? colorVertexGLSL : 
                                    (vertex == MATERIAL_VERTEX) ? materialVertexGLSL :
                                                                  textureVertexGLSL;
    return shadingPath + shaderPath + vertexPath;
}
