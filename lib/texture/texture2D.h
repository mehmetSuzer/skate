
#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include <stb_image.h>
#include <shader.h>

class Texture2D {
private:
    static float borderColor[4];
    GLuint ID;

public:
    Texture2D(const char* imageFile, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter);

    GLuint GetID(void) const;

    void Bind(GLuint unit) const;
    void Unbind(void) const;
    void Delete(void) const;

    static void SetBorderColor(float red, float green, float blue, float alpha);
};

#endif // __TEXTURE2D_H__
