
#include "texture.h"

namespace skate 
{
    Texture Texture::black;
    Texture Texture::gray;
    Texture Texture::white;

    Texture::Texture() {}
    
    Texture::Texture(const std::string path_, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter) : path(path_) 
    {
        int imageWidth, imageHeight, colorChannelNumber;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(path.c_str(), &imageWidth, &imageHeight, &colorChannelNumber, 0);

        if (bytes == NULL) 
            throw Exception("Failed to read " + path);

        if (colorChannelNumber != 1 && colorChannelNumber != 3 && colorChannelNumber != 4) 
            throw Exception("Invalid Color Channel: " + std::to_string(colorChannelNumber));

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        // (S, T, R) -> (X, Y, Z)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            imageWidth,
            imageHeight,
            0,
            (colorChannelNumber == 4) ? GL_RGBA : (colorChannelNumber == 3) ? GL_RGB : GL_RED,
            GL_UNSIGNED_BYTE,
            bytes
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::InitializeCommonTextures(void) noexcept
    {
        Texture::black = Texture("data/textures/general/black.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
        Texture::gray  = Texture("data/textures/general/gray.png",  GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
        Texture::white = Texture("data/textures/general/white.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
    }

    void Texture::DeleteCommonTextures(void) noexcept
    {
        Texture::black.Delete();
        Texture::gray.Delete();
        Texture::white.Delete();
    }
}
