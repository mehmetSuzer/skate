
#ifndef __SHADER_H__
#define __SHADER_H__

#include <fstream>
#include <error.h>
#include <common.h>

typedef enum {
    VERTEX_SHADER_COMPILE_ERROR,
    FRAGMENT_SHADER_COMPILE_ERROR,
    SHADER_PROGRAM_LINKING_ERROR,
} ShaderError;

class Shader {
private:
    static const GLsizei shaderInfoLogSize = 1024;
    GLuint ID;

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    GLuint GetID(void) const {
        return ID;
    }

    void Use(void) const {
    glUseProgram(ID);
    }

    void Delete(void) const {
        glDeleteProgram(ID);
    }

    void SetUniformInt(GLint value, const char* uniform) const {
        glUniform1i(glGetUniformLocation(ID, uniform), value);
    }

    void SetUniformFloat(GLfloat value, const char* uniform) const {
        glUniform1f(glGetUniformLocation(ID, uniform), value);
    }

    void SetUniformVec3(const glm::vec3& vector, const char* uniform) const {
        glUniform3f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z);
    }

    void SetUniformVec4(const glm::vec4& vector, const char* uniform) const {
        glUniform4f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z, vector.w);
    }

    void SetUniformMat3(const glm::mat3& matrix, const char* uniform) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void SetUniformMat4(const glm::mat4& matrix, const char* uniform) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void CheckShaderError(GLuint shader, ShaderError type) const;
};

#endif // __SHADER_H__
