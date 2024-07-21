
#include "shader.h"

namespace skate 
{
    Shader::Shader(util::VertexType vertex) 
    {
        GLint success;
        GLchar shaderInfoLog[1024];

        const std::string vertexShaderPath = util::GetShaderProgramPath(util::VERTEX_SHADER, vertex);
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const std::string vertexShaderCode = util::ReadFile(vertexShaderPath);
        const char* vertexShaderSource = vertexShaderCode.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            glGetShaderInfoLog(vertexShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            const std::string message = "SHADER::VERTEX::COMPILATION_FAILED\nFile Path: " + vertexShaderPath + "\n" + shaderInfoLog;
            throw Exception(message);
        }

        const std::string fragmentShaderPath = util::GetShaderProgramPath(util::FRAGMENT_SHADER, vertex);
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const std::string fragmentShaderCode = util::ReadFile(fragmentShaderPath);
        const char* fragmentShaderSource = fragmentShaderCode.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            glGetShaderInfoLog(fragmentShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            const std::string message = "SHADER::FRAGMENT::COMPILATION_FAILED\nFile Path: " + fragmentShaderPath + "\n" + shaderInfoLog;
            throw Exception(message);
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) 
        {
            glGetProgramInfoLog(ID, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            const std::string message = "SHADER::PROGRAM::LINKING_FAILED\n" + std::string(shaderInfoLog);
            throw Exception(message);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::Update(const glm::mat4& projectionView, const glm::vec3& cameraPosition, const std::vector<LightCaster*>& lightCasters) const noexcept 
    {
        Use();
        SetUniformMat4(projectionView, "projectionView");
        SetUniformVec3(cameraPosition, "cameraPosition");

        uint32_t lightCasterNumber = (lightCasters.size() < MAX_LIGHT_CASTER_NUMBER) ? lightCasters.size() : MAX_LIGHT_CASTER_NUMBER;
        SetUniformInt(lightCasterNumber, "lightCasterNumber");

        for (uint32_t j = 0; j < lightCasterNumber; j++) 
        {
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
}
