
#include "vbo.h"

void VBO::Bind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(void) const {
    glDeleteBuffers(1, &ID);
}
