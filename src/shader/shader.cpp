
#include "shader.h"

namespace skate 
{
    std::string Shader::ReadShaderSource(const char* filename) 
    {
        const std::string path = std::string("glsl/") + filename;
        std::ifstream file(path);
        assert(file.is_open());

        std::stringstream buffer;
        std::string line;
        while (std::getline(file, line)) 
        {
            if (line.find("#include") != std::string::npos) 
            {
                size_t start = line.find_first_of('<');
                size_t end = line.find_last_of('>');
                assert(start != std::string::npos && end != std::string::npos); // Check invalid source include

                std::string includeFilename = line.substr(start+1, end-start-1);
                std::string includeSource = ReadShaderSource(includeFilename.c_str());
                buffer << includeSource << std::endl;
            } 
            else
                buffer << line << std::endl;
        }
        return buffer.str();
    }

    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
    {
        GLint success;
        GLchar shaderInfoLog[1024];
        assert(vertexShaderPath != NULL && fragmentShaderPath != NULL);

        //-------------------------------------- VERTEX SHADER --------------------------------------//

        const std::string vertexShaderCode = ReadShaderSource(vertexShaderPath);
        const char* vertexShaderSource = vertexShaderCode.c_str();
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

    #ifdef __SHADER_DEBUG__
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(vertexShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
        std::cout << "SHADER COMPILATION: " << vertexShaderPath << " --> " << ((strlen(shaderInfoLog) != 0) ? shaderInfoLog : "SUCCESS") << std::endl;
        assert(success); // Check whether the shader is compiled successfully
    #endif 

        //-------------------------------------- GEOMETRY SHADER --------------------------------------//

        GLuint geometryShader;
        if (geometryShaderPath != NULL)
        {
            const std::string geometryShaderCode = ReadShaderSource(geometryShaderPath);
            const char* geometryShaderSource = geometryShaderCode.c_str();
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
            glCompileShader(geometryShader);

        #ifdef __SHADER_DEBUG__
            glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
            glGetShaderInfoLog(geometryShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
            std::cout << "SHADER COMPILATION: " << geometryShaderPath << " --> " << ((strlen(shaderInfoLog) != 0) ? shaderInfoLog : "SUCCESS") << std::endl;
            assert(success); // Check whether the shader is compiled successfully
        #endif 
        }

        //-------------------------------------- FRAGMENT SHADER --------------------------------------//

        const std::string fragmentShaderCode = ReadShaderSource(fragmentShaderPath);
        const char* fragmentShaderSource = fragmentShaderCode.c_str();
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

    #ifdef __SHADER_DEBUG__
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(fragmentShader, sizeof(shaderInfoLog), NULL, shaderInfoLog);
        std::cout << "SHADER COMPILATION: " << fragmentShaderPath << " --> " << ((strlen(shaderInfoLog) != 0) ? shaderInfoLog : "SUCCESS") << std::endl;
        assert(success); // Check whether the shader is compiled successfully
    #endif

        //-------------------------------------- LINKING --------------------------------------//

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        if (geometryShaderPath != NULL)
            glAttachShader(ID, geometryShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

    #ifdef __SHADER_DEBUG__
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        glGetProgramInfoLog(ID, sizeof(shaderInfoLog), NULL, shaderInfoLog);
        std::cout << "SHADER LINKING: " << ((strlen(shaderInfoLog) != 0) ? shaderInfoLog : "SUCCESS") << std::endl << std::endl;
        assert(success); // Check whether the shader is linked successfully
    #endif

        glDeleteShader(vertexShader);
        if (geometryShaderPath != NULL)
            glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
    }
}
