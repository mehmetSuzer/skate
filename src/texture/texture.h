
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "stb_image.h"
#include "exception.h"
#include "glad.h"
#include "util.h"

namespace skate 
{
    class Texture
    {
    private:
        GLuint ID;
        std::string path;

        Texture();
        
    public:
        static Texture black;
        static Texture gray;
        static Texture white;

        Texture(const std::string path_, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter);

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

        static void InitializeCommonTextures(void) noexcept;
        static void DeleteCommonTextures(void) noexcept;
    };
}

#endif // __TEXTURE_H__
