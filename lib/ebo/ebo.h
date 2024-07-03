
#ifndef __EBO_H__
#define __EBO_H__

#include <vector>
#include "glad.h"

class EBO {
private:
    GLuint ID;

public:
    EBO(const std::vector<GLuint>& indices);

    void Bind(void) const;
    void Unbind(void) const;
    void Delete(void) const;
};


#endif // __EBO_H__
