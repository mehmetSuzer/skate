
#include "shader.h"

namespace skate 
{
    std::string Shader::ReadShaderSource(const std::string& filename) 
    {
        const std::string path = "glsl/" + filename;
        std::ifstream file(path);
        if (!file.is_open())
            throw Exception("File " + path + " couldn't be found!");

        std::stringstream buffer;
        std::string line;
        while (std::getline(file, line)) 
        {
            if (line.find("#include") != std::string::npos) 
            {
                size_t start = line.find_first_of('<');
                size_t end = line.find_last_of('>');
                if (start != std::string::npos && end != std::string::npos) 
                {
                    std::string includeFilename = line.substr(start+1, end-start-1);
                    std::string includeSource = ReadShaderSource(includeFilename);
                    buffer << includeSource << std::endl;
                } 
                else
                    throw Exception("Invalid source include! Line: " + line);
            } 
            else
                buffer << line << std::endl;
        }
        return buffer.str();
    }

    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) 
    {
        GLint success;
        GLchar shaderInfoLog[1024];

        const std::string vertexShaderCode = ReadShaderSource(vertexShaderPath);
        const char* vertexShaderSource = vertexShaderCode.c_str();
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            glGetShaderInfoLog(vertexShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            throw Exception("SHADER::VERTEX::COMPILATION_FAILED\nFile Path: " + vertexShaderPath + "\n" + shaderInfoLog);
        }

        const std::string fragmentShaderCode = ReadShaderSource(fragmentShaderPath);
        const char* fragmentShaderSource = fragmentShaderCode.c_str();
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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
