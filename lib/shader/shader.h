
#ifndef __SHADER_H__
#define __SHADER_H__

#include <vector>
#include "exception.h"
#include "util.h"
#include "light.h"
#include "gtc/type_ptr.hpp"

// Update shaders as well when you update this
#define MAX_LIGHT_CASTER_NUMBER 8

enum ShaderError {
    VERTEX_SHADER_COMPILE_ERROR = 0,
    FRAGMENT_SHADER_COMPILE_ERROR,
    SHADER_PROGRAM_LINKING_ERROR,
};

class Shader {
private:
    static const GLsizei shaderInfoLogSize = 1024;
    GLuint ID;

    void CheckShaderError(GLuint shader, enum ShaderError type, const char* filePath) const;
    
public:
    Shader(util::VertexType vertex);

    inline GLuint GetID(void) const noexcept {
        return ID;
    }

    inline void Use(void) const noexcept {
        glUseProgram(ID);
    }

    inline void Delete(void) const noexcept {
        glDeleteProgram(ID);
    }

    inline void SetUniformInt(GLint value, const char* uniform) const noexcept {
        glUniform1i(glGetUniformLocation(ID, uniform), value);
    }

    inline void SetUniformFloat(GLfloat value, const char* uniform) const noexcept {
        glUniform1f(glGetUniformLocation(ID, uniform), value);
    }

    inline void SetUniformVec3(const glm::vec3& vector, const char* uniform) const noexcept {
        glUniform3f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z);
    }

    inline void SetUniformVec4(const glm::vec4& vector, const char* uniform) const noexcept {
        glUniform4f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z, vector.w);
    }

    inline void SetUniformMat3(const glm::mat3& matrix, const char* uniform) const noexcept {
        glUniformMatrix3fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    inline void SetUniformMat4(const glm::mat4& matrix, const char* uniform) const noexcept {
        glUniformMatrix4fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Update(const glm::mat4& projectionView, const glm::vec3& cameraPosition, const std::vector<LightCaster*>& lightCasters) const noexcept;
};

#endif // __SHADER_H__
