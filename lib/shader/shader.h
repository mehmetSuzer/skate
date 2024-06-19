
#ifndef __SHADER_H__
#define __SHADER_H__

#include <iostream>
#include <fstream>

#include <error.h>
#include <glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define SHADER_INFO_LOG_SIZE ((GLsizei)1024)

typedef enum {
    VERTEX_SHADER_COMPILE_ERROR,
    FRAGMENT_SHADER_COMPILE_ERROR,
    SHADER_PROGRAM_LINKING_ERROR,
} ShaderError;

class Shader {
private:
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
