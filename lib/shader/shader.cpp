
#include "shader.h"

std::string readFile(const char* filename) {
    std::ifstream in(filename, std::ios::binary);

    #if COMPILE_ERROR_HANDLERS
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

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = readFile(vertexShaderPath);
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

#if COMPILE_ERROR_HANDLERS
    CheckShaderError(vertexShader, VERTEX_SHADER_COMPILE_ERROR);
#endif

    /* ----------------------------------------------------------------- */

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = readFile(fragmentShaderPath);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

#if COMPILE_ERROR_HANDLERS
    CheckShaderError(fragmentShader, FRAGMENT_SHADER_COMPILE_ERROR);
#endif 

    /* ----------------------------------------------------------------- */

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

#if COMPILE_ERROR_HANDLERS
    CheckShaderError(ID, SHADER_PROGRAM_LINKING_ERROR);
#endif

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::CheckShaderError(GLuint shader, ShaderError type) const {
    GLint success;
    GLchar shaderInfoLog[shaderInfoLogSize];

    if (type == VERTEX_SHADER_COMPILE_ERROR || type == FRAGMENT_SHADER_COMPILE_ERROR) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, shaderInfoLogSize, NULL, shaderInfoLog);
            std::string shaderType = (type == VERTEX_SHADER_COMPILE_ERROR) ? "VERTEX" : "FRAGMENT";
            std::string errorMessage = "ERROR::SHADER::" + shaderType + "::COMPILATION_FAILED\n" + std::string(shaderInfoLog);
            throw Error(errorMessage);
        }
    } else if (type == SHADER_PROGRAM_LINKING_ERROR) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, shaderInfoLogSize, NULL, shaderInfoLog);
            std::string errorMessage = "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(shaderInfoLog);
            throw Error(errorMessage);
        }
    } else {
        std::string errorMessage = "Invalid Shader Error Type: " + std::to_string(type);
        throw Error(errorMessage);
    }
}
