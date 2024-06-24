
#include "vao.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttribute(VBO& VBO, GLuint layout, GLint componentNumber, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const {
    VBO.Bind();
    glVertexAttribPointer(layout, componentNumber, type, normalized, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind(void) const {
    glBindVertexArray(ID);
}
    
void VAO::Unbind(void) const {
    glBindVertexArray(0);
}
    
void VAO::Delete(void) const {
    glDeleteVertexArrays(1, &ID);
}
