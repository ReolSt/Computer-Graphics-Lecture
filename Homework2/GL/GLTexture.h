#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <gl/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "core/std_image.h"

class GLTexture
{
public:
    GLTexture()
    {
        glGenTextures(1, &this->id);
        glBindTexture(GL_TEXTURE_2D, this->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    virtual ~GLTexture()
    {
        glDeleteTextures(1, &this->id);
    }

    unsigned int GetId()
    {
        return this->id;
    }

    int GetWidth()
    {
        return this->width;
    }

    int GetHeight()
    {
        return this->height;
    }

    int GetChannels()
    {
        return this->channels;
    }

    void Use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->id);
    }

    void Load(const std::string& fileName, GLenum colorMode = GL_RGB, GLenum pixelType = GL_UNSIGNED_BYTE)
    {
        unsigned char* data = stbi_load(fileName.c_str(), &this->width, &this->height, &this->channels, 0);

        assert(data != NULL);

        glBindTexture(GL_TEXTURE_2D, this->id);
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode , this->width, this->height, 0, colorMode, pixelType, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    unsigned int id = -1;

    int width = 0;
    int height = 0;
    int channels = 0;
};