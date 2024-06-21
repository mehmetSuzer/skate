
#ifndef __VBO_H__
#define __VBO_H__

#include <vector>
#include <glad.h>
#include <glm.hpp>

#define BASIC_VERTEX    0
#define NORMAL_VERTEX   1
#define TEXTURE_VERTEX  2
#define COLOR_VERTEX    3

typedef struct {
    glm::vec3 position;
} BasicVertex;

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
} NormalVertex;

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
} TextureVertex;

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
} ColorVertex;

class VBO {
private:
    GLuint ID;

public:
    template<typename T>
    VBO(const std::vector<T>& vertices, GLenum usage) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), usage);
    }

    void Bind(void) const;
    void Unbind(void) const;
    void Delete(void) const;
};

#endif // __VBO_H__
