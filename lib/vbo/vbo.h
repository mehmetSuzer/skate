
#ifndef __VBO_H__
#define __VBO_H__

#include <type_traits>
#include <vector>
#include <glad.h>
#include <glm.hpp>

// Just Position
typedef struct {
    glm::vec3 position;
} PVertex;

// Position + Normal
typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
} PNVertex;

// Position + Normal + Texture
typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
} PNTVertex;

// Position + Normal + Color
typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
} PNCVertex;

template<typename T>
struct isAValidVertex {
    static constexpr bool value = std::is_same<T, PVertex>::value   ||
                                  std::is_same<T, PNVertex>::value  ||
                                  std::is_same<T, PNTVertex>::value ||
                                  std::is_same<T, PNCVertex>::value;
};


class VBO {
private:
    GLuint ID;

public:
    template<typename T>
    VBO(const std::vector<T>& vertices, GLenum usage) {
        static_assert(isAValidVertex<T>::value, "T must be one of PVertex, PNVertex, PNTVertex, and PNCVertex!");
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), usage);
    }

    void Bind(void) const;
    void Unbind(void) const;
    void Delete(void) const;
};

#endif // __VBO_H__
