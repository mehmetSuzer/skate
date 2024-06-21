
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

    GLuint GetID(void) const;
    void Use(void) const;
    void Delete(void) const;

    void SetUniformInt(GLint value, const char* uniform) const;
    void SetUniformFloat(GLfloat value, const char* uniform) const;
    void SetUniformVec4(const glm::vec4& vector, const char* uniform) const;
    void SetUniformMat4(const glm::mat4& matrix, const char* uniform) const;

    void CheckShaderError(GLuint shader, ShaderError type) const;
};

#endif // __SHADER_H__
