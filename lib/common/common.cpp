
#include "common.h"

Common Common::instance;

const std::string Common::GetShaderProgramPath(enum ShadingType shading, enum ShaderType shader, enum VertexType vertex) const {
    const std::string& shadingPath = (shading == FLAT_SHADING)    ? flatShadingPath : 
                                     (shading == GOURAUD_SHADING) ? gouraudShadingPath : 
                                                                    phongShadingPath;

    const std::string& shaderPath = (shader == VERTEX_SHADER) ? vertexShaderPath : 
                                                                fragmentShaderPath;

    const std::string& vertexPath = (vertex == BASIC_VERTEX)  ? basicVertexGLSL : 
                                    (vertex == COLOR_VERTEX)  ? colorVertexGLSL : 
                                    (vertex == NORMAL_VERTEX) ? normalVertexGLSL : 
                                                                textureVertexGLSL;
                                                                    
    return shadingPath + shaderPath + vertexPath;
}
