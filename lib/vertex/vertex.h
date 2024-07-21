
#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <type_traits>
#include "glad.h"
#include "glm.hpp"

// Position + Normal
struct MaterialVertex {
    glm::vec3 position;
    glm::vec3 normal;

    static void LinkAttributes(void) noexcept {
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, position));
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, normal));
    }
};

// Position + Normal + Texture
struct TextureVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    static void LinkAttributes(void) noexcept {
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)offsetof(TextureVertex, position));
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)offsetof(TextureVertex, normal));
        // texture
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)offsetof(TextureVertex, texture));
    }
};

// Position + Normal + Color
struct ColorVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;

    static void LinkAttributes(void) noexcept {
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, position));
        // normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, normal));
        // color
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, color));
    }
};

template<typename Vertex>
struct isAValidVertex {
    static constexpr bool value = std::is_same<Vertex, ColorVertex>::value    ||
                                  std::is_same<Vertex, MaterialVertex>::value ||
                                  std::is_same<Vertex, TextureVertex>::value;
};

#endif // __VERTEX_H__
