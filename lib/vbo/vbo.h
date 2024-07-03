
#ifndef __VBO_H__
#define __VBO_H__

#include <type_traits>
#include <vector>
#include <glad.h>
#include <glm.hpp>
#include <vertex.h>

template<typename Vertex>
struct isAValidVertex {
    static constexpr bool value = std::is_same<Vertex, PVertex>::value   ||
                                  std::is_same<Vertex, PNVertex>::value  ||
                                  std::is_same<Vertex, PNTVertex>::value ||
                                  std::is_same<Vertex, PNCVertex>::value;
};

class VBO {
private:
    GLuint ID;

public:
    template<typename Vertex>
    VBO(const std::vector<Vertex>& vertices, GLenum usage) {
        static_assert(isAValidVertex<Vertex>::value, "Vertex must be one of PVertex, PNVertex, PNTVertex, and PNCVertex!");
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), usage);
    }

    void Bind(void) const;
    void Unbind(void) const;
    void Delete(void) const;
};

#endif // __VBO_H__
