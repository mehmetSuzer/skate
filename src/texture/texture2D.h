
#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include "stb_image.h"
#include "exception.h"
#include "glad.h"

namespace skate 
{
    class Texture2D 
    {
    private:
        static float borderColor[4];

        GLuint ID;
        const std::string path;

    public:
        Texture2D(const std::string& path_, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter);

        inline GLuint GetID(void) const noexcept 
        {
            return ID;
        }

        inline const std::string& GetPath(void) const noexcept 
        {
            return path;
        }

        inline void Delete(void) const noexcept 
        {
            glDeleteTextures(1, &ID);
        }

        static void SetBorderColor(float red, float green, float blue, float alpha) noexcept;
    };
}

#endif // __TEXTURE2D_H__
