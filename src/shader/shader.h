
#ifndef __SHADER_H__
#define __SHADER_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "config.h"
#include "light_caster.h"

// Update shaders as well when you update this
#define MAX_LIGHT_CASTER_NUMBER 8

namespace skate 
{
    // Programs that rest on the GPU and run for each specific section of the graphics pipeline
    class Shader 
    {
    private:
        GLuint ID;
        
        static std::string ReadShaderSource(const char* filename);

    public:
        // Shader paths must be with respect to glsl/ folder. glsl/ part is automatically added in the method.
        // E.g. vertex/texture_shader.glsl, fragment/texture_shader.glsl, or geometry/pass_through.glsl
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShader = NULL);

        inline GLuint GetID(void) const noexcept 
        {
            return ID;
        }

        inline void Use(void) const noexcept 
        {
            glUseProgram(ID);
        }

        inline void Delete(void) const noexcept 
        {
            glDeleteProgram(ID);
        }

        inline void SetUniformBool(bool value, const char* uniform) const noexcept 
        {
            glUniform1i(glGetUniformLocation(ID, uniform), (GLint)value);
        }

        inline void SetUniformInt(GLint value, const char* uniform) const noexcept 
        {
            glUniform1i(glGetUniformLocation(ID, uniform), value);
        }

        inline void SetUniformFloat(GLfloat value, const char* uniform) const noexcept 
        {
            glUniform1f(glGetUniformLocation(ID, uniform), value);
        }

        inline void SetUniformVec3(const glm::vec3& vector, const char* uniform) const noexcept 
        {
            glUniform3f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z);
        }

        inline void SetUniformVec4(const glm::vec4& vector, const char* uniform) const noexcept 
        {
            glUniform4f(glGetUniformLocation(ID, uniform), vector.x, vector.y, vector.z, vector.w);
        }

        inline void SetUniformMat3(const glm::mat3& matrix, const char* uniform) const noexcept 
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
        }

        inline void SetUniformMat4(const glm::mat4& matrix, const char* uniform) const noexcept 
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
        }

        void UpdateLightCasters(const std::vector<LightCaster*>& lightCasters) const noexcept;
        void UpdateView(const glm::mat4& projectionView, const glm::vec3& cameraPosition) const noexcept;
    };
}

#endif // __SHADER_H__
