
#include "shader.h"

Shader::Shader(util::ShadingType shading, util::VertexType vertex) {
    if (shading == util::GOURAUD_SHADING && vertex == util::TEXTURE_VERTEX) {
        throw Exception("Gouraud shading does not support Texture Vertices!");    
    }

    const std::string vertexShaderPath = util::GetShaderProgramPath(shading, util::VERTEX_SHADER, vertex);
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertexShaderCode = util::ReadFile(vertexShaderPath);
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckShaderError(vertexShader, VERTEX_SHADER_COMPILE_ERROR, vertexShaderPath.c_str());

    const std::string fragmentShaderPath = util::GetShaderProgramPath(shading, util::FRAGMENT_SHADER, vertex);
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string fragmentShaderCode = util::ReadFile(fragmentShaderPath);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    CheckShaderError(fragmentShader, FRAGMENT_SHADER_COMPILE_ERROR, fragmentShaderPath.c_str());

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    CheckShaderError(ID, SHADER_PROGRAM_LINKING_ERROR, NULL);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetUniforms(const glm::mat4& projectionView, const glm::vec3& cameraPosition, const std::vector<LightCaster*>& lightCasters) const {
    Use();
    SetUniformMat4(projectionView, "projectionView");
    SetUniformVec3(cameraPosition, "cameraPosition");

    uint32_t lightCasterNumber = (lightCasters.size() < MAX_LIGHT_CASTER_NUMBER) ? lightCasters.size() : MAX_LIGHT_CASTER_NUMBER;
    SetUniformInt(lightCasterNumber, "lightCasterNumber");

    for (uint32_t j = 0; j < lightCasterNumber; j++) {
        const Light light = lightCasters[j]->GetLight();
        const std::string arrayString = "lights[" + std::to_string(j) + "].";

        SetUniformInt(light.type, (arrayString + "type").c_str());
        SetUniformVec3(light.color, (arrayString + "color").c_str());
        SetUniformVec3(light.position, (arrayString + "position").c_str());
        SetUniformVec3(light.direction, (arrayString + "direction").c_str());
        SetUniformFloat(light.intensity, (arrayString + "intensity").c_str());
        SetUniformFloat(light.linear, (arrayString + "linear").c_str());
        SetUniformFloat(light.quadratic, (arrayString + "quadratic").c_str());
        SetUniformFloat(light.cosInnerCutOff, (arrayString + "cosInnerCutOff").c_str());
        SetUniformFloat(light.cosOuterCutOff, (arrayString + "cosOuterCutOff").c_str());
    }
}

void Shader::CheckShaderError(GLuint shader, enum ShaderError type, const char* filePath) const {
    GLint success;
    GLchar shaderInfoLog[shaderInfoLogSize];

    if (type == VERTEX_SHADER_COMPILE_ERROR || type == FRAGMENT_SHADER_COMPILE_ERROR) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, shaderInfoLogSize, NULL, shaderInfoLog);
            const std::string shaderType = (type == VERTEX_SHADER_COMPILE_ERROR) ? "VERTEX" : "FRAGMENT";
            const std::string message = "SHADER::" + shaderType + "::COMPILATION_FAILED\nFile Path: " + 
            std::string(filePath) + "\n" + std::string(shaderInfoLog);
            throw Exception(message);
        }
    } else if (type == SHADER_PROGRAM_LINKING_ERROR) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, shaderInfoLogSize, NULL, shaderInfoLog);
            const std::string message = "SHADER::PROGRAM::LINKING_FAILED\nFile Path: " + 
            std::string(filePath) + "\n" + std::string(shaderInfoLog);
            throw Exception(message);
        }
    } else {
        const std::string message = "Invalid Shader Error Type: " + std::to_string(type);
        throw Exception(message);
    }
}
