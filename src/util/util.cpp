
#include "util.h"

namespace skate 
{
    namespace util 
    {
        const std::string glslPath = "glsl/";
        const std::string vertexShaderDir = "vertex/";
        const std::string fragmentShaderDir = "fragment/";

        const std::string glslFileExtension = ".glsl";
        const std::string colorVertexGLSL = "color" + glslFileExtension;
        const std::string materialVertexGLSL = "material" + glslFileExtension;
        const std::string textureVertexGLSL = "texture" + glslFileExtension;

        const std::string dataDir = "data/";
        const std::string modelsDir = dataDir + "models/";
        const std::string texturesDir = dataDir + "textures/";

        const glm::vec4 backgroundColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);

        GLsizei windowWidth = 1000;
        GLsizei windowHeight = 800;
        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        
        void SetWindowWidthAndHeight(int windowWidth_, int windowHeight_) noexcept 
        {
            windowWidth = windowWidth_;
            windowHeight = windowHeight_;
            aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        }

        std::string ReadFile(const std::string& filename) 
        {
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) 
                throw Exception("File " + filename + " couldn't be found!");
            
            std::string contents;
            file.seekg(0, std::ios::end);
            contents.resize(file.tellg());
            file.seekg(0, std::ios::beg);
            file.read(&contents[0], contents.size());
            file.close();
            return contents;
        }

        // filename must be with respect to glsl/
        std::string ReadShaderSource(const std::string& filename) 
        {
            const std::string path = glslPath + filename;
            std::ifstream file(path);
            if (!file.is_open())
                throw Exception("File " + path + "couldn't be found!");

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

        const std::string GetShaderProgramPath(enum ShaderType shader, enum VertexType vertex) noexcept 
        {
            const std::string& shaderDir = (shader == VERTEX_SHADER) ? vertexShaderDir : 
                                                                       fragmentShaderDir;

            const std::string& filename = (vertex == COLOR_VERTEX)    ? colorVertexGLSL : 
                                          (vertex == MATERIAL_VERTEX) ? materialVertexGLSL :
                                                                        textureVertexGLSL;
            return shaderDir + filename;
        }
    }
}
