
#include "shader.h"

std::string readFile(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    std::string errorMessage = "File " + std::string(filename) + " couldn't be found!";
    throw Error(errorMessage);
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = readFile(vertexShaderPath);
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckShaderError(vertexShader, VERTEX_SHADER_COMPILE_ERROR);

    /* ----------------------------------------------------------------- */

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = readFile(fragmentShaderPath);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    CheckShaderError(fragmentShader, FRAGMENT_SHADER_COMPILE_ERROR);

    /* ----------------------------------------------------------------- */

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    CheckShaderError(ID, SHADER_PROGRAM_LINKING_ERROR);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::GetID(void) const {
    return ID;
}

void Shader::Use(void) const {
    glUseProgram(ID);
}

void Shader::Delete(void) const {
    glDeleteProgram(ID);
}

void Shader::SetUniformInt(GLint value, const char* uniform) const {
    glUniform1i(glGetUniformLocation(ID, uniform), value);
}

void Shader::SetUniformFloat(GLfloat value, const char* uniform) const {
    glUniform1f(glGetUniformLocation(ID, uniform), value);
}

void Shader::SetUniformVec4(const glm::vec4& vector, const char* uniform) const {
    glUniform4f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z, vector.w);
}

void Shader::SetUniformMat4(const glm::mat4& matrix, const char* uniform) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::CheckShaderError(GLuint shader, ShaderError type) const {
    GLint success;
    GLchar shaderInfoLog[SHADER_INFO_LOG_SIZE];

    if (type == VERTEX_SHADER_COMPILE_ERROR || type == FRAGMENT_SHADER_COMPILE_ERROR) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, SHADER_INFO_LOG_SIZE, NULL, shaderInfoLog);
            std::string shaderType = (type == VERTEX_SHADER_COMPILE_ERROR) ? "VERTEX" : "FRAGMENT";
            std::string errorMessage = "ERROR::SHADER::" + shaderType + "::COMPILATION_FAILED\n" + std::string(shaderInfoLog);
            throw Error(errorMessage);
        }
    } else if (type == SHADER_PROGRAM_LINKING_ERROR) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, SHADER_INFO_LOG_SIZE, NULL, shaderInfoLog);
            std::string errorMessage = "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(shaderInfoLog);
            throw Error(errorMessage);
        }
    } else {
        std::string errorMessage = "Invalid Shader Error Type: " + std::to_string(type);
        throw Error(errorMessage);
    }
}