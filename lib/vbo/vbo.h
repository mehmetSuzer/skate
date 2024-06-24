
#ifndef __VBO_H__
#define __VBO_H__

#include <type_traits>
#include <vector>
#include <glad.h>
#include <glm.hpp>

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

template<typename T>
struct isAValidVertex {
    static constexpr bool value = std::is_same<T, BasicVertex>::value   ||
                                  std::is_same<T, NormalVertex>::value  ||
                                  std::is_same<T, TextureVertex>::value ||
                                  std::is_same<T, ColorVertex>::value;
};


class VBO {
private:
    GLuint ID;

public:
    template<typename T>
    VBO(const std::vector<T>& vertices, GLenum usage) {
        static_assert(isAValidVertex<T>::value, "T must be one of BasicVertex, NormalVertex, TextureVertex, and ColorVertex!");
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), usage);
    }

    void Bind(void) const;
    void Unbind(void) const;
    void Delete(void) const;
};

#endif // __VBO_H__
