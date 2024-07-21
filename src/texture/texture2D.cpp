
#include "texture2D.h"

namespace skate 
{
    float Texture2D::borderColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    Texture2D::Texture2D(const std::string& path_, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter) : path(path_) 
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

        // Set border color if GL_CLAMP_TO_BORDER is used
        if (wrapS == GL_CLAMP_TO_BORDER || wrapT == GL_CLAMP_TO_BORDER) 
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        
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

    void Texture2D::SetBorderColor(float red, float green, float blue, float alpha) noexcept 
    {
        Texture2D::borderColor[0] = red;
        Texture2D::borderColor[1] = green;
        Texture2D::borderColor[2] = blue;
        Texture2D::borderColor[3] = alpha;
    }
}
