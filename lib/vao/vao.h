
#ifndef __VAO_H__
#define __VAO_H__

#include <vbo.h>

class VAO {
private:
    GLuint ID;

public:
    VAO();
    
    void LinkAttribute(VBO& VBO, GLuint layout, GLint componentNumber, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const;

    void Bind(void) const;
    void Unbind(void) const;
    void Delete(void) const;
};

#endif // __VAO_H__
