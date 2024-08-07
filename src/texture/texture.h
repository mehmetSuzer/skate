
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include <assert.h>
#include "glad.h"
#include "stb_image.h"

namespace skate 
{
    // An image used to add details to an object.
    // Currently, only 2D textures are supported.
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

        Texture(const std::string path_, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, 
            GLint minFilter = GL_NEAREST, GLint magFilter = GL_NEAREST);

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
