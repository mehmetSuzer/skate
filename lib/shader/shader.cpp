
#include "shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = Common::Instance().ReadFile(vertexShaderPath);
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

#ifdef __COMPILE_ERROR_HANDLERS__
    CheckShaderError(vertexShader, VERTEX_SHADER_COMPILE_ERROR, vertexShaderPath);
#endif

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = Common::Instance().ReadFile(fragmentShaderPath);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

#ifdef __COMPILE_ERROR_HANDLERS__
    CheckShaderError(fragmentShader, FRAGMENT_SHADER_COMPILE_ERROR, fragmentShaderPath);
#endif 

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

#ifdef __COMPILE_ERROR_HANDLERS__
    CheckShaderError(ID, SHADER_PROGRAM_LINKING_ERROR, NULL);
#endif

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::CheckShaderError(GLuint shader, enum ShaderError type, const char* filePath) const {
    GLint success;
    GLchar shaderInfoLog[shaderInfoLogSize];

    if (type == VERTEX_SHADER_COMPILE_ERROR || type == FRAGMENT_SHADER_COMPILE_ERROR) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, shaderInfoLogSize, NULL, shaderInfoLog);
            const std::string shaderType = (type == VERTEX_SHADER_COMPILE_ERROR) ? "VERTEX" : "FRAGMENT";
            const std::string errorMessage = "ERROR::SHADER::" + shaderType + "::COMPILATION_FAILED\nFile Path: " + 
                std::string(filePath) + "\n" + std::string(shaderInfoLog);
            throw Error(errorMessage);
        }
    } else if (type == SHADER_PROGRAM_LINKING_ERROR) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, shaderInfoLogSize, NULL, shaderInfoLog);
            const std::string errorMessage = "ERROR::SHADER::PROGRAM::LINKING_FAILED\nFile Path: " + 
                std::string(filePath) + "\n" + std::string(shaderInfoLog);
            throw Error(errorMessage);
        }
    } else {
        const std::string errorMessage = "Invalid Shader Error Type: " + std::to_string(type);
        throw Error(errorMessage);
    }
}
