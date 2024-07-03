
#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <type_traits>
#include "glad.h"
#include "glm.hpp"

// Position + Normal
struct PNVertex {
    glm::vec3 position;
    glm::vec3 normal;

    static void LinkAttributes(void) {
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PNVertex), (void*)0);
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PNVertex), (void*)sizeof(PNVertex::position));
    }
};

// Position + Normal + Texture
struct PNTVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    static void LinkAttributes(void) {
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)0);
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)sizeof(PNTVertex::position));
        // texture
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)(sizeof(PNTVertex::position) + sizeof(PNTVertex::normal)));
    }
};

// Position + Normal + Color
struct PNCVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;

    static void LinkAttributes(void) {
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PNCVertex), (void*)0);
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PNCVertex), (void*)sizeof(PNCVertex::position));
        // color
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(PNCVertex), (void*)(sizeof(PNCVertex::position) + sizeof(PNCVertex::normal)));
    }
};

template<typename Vertex>
struct isAValidVertex {
    static constexpr bool value = std::is_same<Vertex, PNVertex>::value  ||
                                  std::is_same<Vertex, PNTVertex>::value ||
                                  std::is_same<Vertex, PNCVertex>::value;
};

#endif // __VERTEX_H__
