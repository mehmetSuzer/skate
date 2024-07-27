
#include "shader.h"

namespace skate 
{
    Shader::Shader(util::VertexType vertex) 
    {
        GLint success;
        GLchar shaderInfoLog[1024];

        const std::string vertexShaderPath = util::GetShaderProgramPath(util::VERTEX_SHADER, vertex);
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const std::string vertexShaderCode = util::ReadShaderSource(vertexShaderPath);
        const char* vertexShaderSource = vertexShaderCode.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            glGetShaderInfoLog(vertexShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            throw Exception("SHADER::VERTEX::COMPILATION_FAILED\nFile Path: " + vertexShaderPath + "\n" + shaderInfoLog);
        }

        const std::string fragmentShaderPath = util::GetShaderProgramPath(util::FRAGMENT_SHADER, vertex);
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const std::string fragmentShaderCode = util::ReadShaderSource(fragmentShaderPath);
        const char* fragmentShaderSource = fragmentShaderCode.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            glGetShaderInfoLog(fragmentShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            throw Exception("SHADER::FRAGMENT::COMPILATION_FAILED\nFile Path: " + fragmentShaderPath + "\n" + shaderInfoLog);
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) 
        {
            glGetProgramInfoLog(ID, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            throw Exception("SHADER::PROGRAM::LINKING_FAILED\n" + std::string(shaderInfoLog));
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::UpdateLightCasters(const std::vector<LightCaster*>& lightCasters) const noexcept
    {
        uint32_t lightCasterNumber = (lightCasters.size() < MAX_LIGHT_CASTER_NUMBER) ? lightCasters.size() : MAX_LIGHT_CASTER_NUMBER;

        Use();
        SetUniformInt(lightCasterNumber, "lightCasterNumber");

        for (uint32_t i = 0; i < lightCasterNumber; i++) 
        {
            const Light light = lightCasters[i]->GetLight();
            const std::string arrayString = "lights[" + std::to_string(i) + "].";

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

    void Shader::UpdateView(const glm::mat4& projectionView, const glm::vec3& cameraPosition) const noexcept 
    {
        Use();
        SetUniformMat4(projectionView, "projectionView");
        SetUniformVec3(cameraPosition, "cameraPosition");
    }
}
