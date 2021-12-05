#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "GLMemoryHelpers.h"
#include "GLTexture.h"

class GLTextureLoader
{
public:
    static GLSharedPtr<GLTexture> Load(const std::string& fileName, GLenum colorMode = GL_RGB, GLenum pixelType = GL_UNSIGNED_BYTE)
    {
        if (loadedTextures.find(fileName) != loadedTextures.end())
        {
            return loadedTextures[fileName];
        }

        auto texture = GLCreate<GLTexture>();
        texture->Load(fileName, colorMode, pixelType);

        loadedTextures[fileName] = texture;

        return texture;
    }

private:
    static std::unordered_map<std::string, GLSharedPtr<GLTexture>> loadedTextures;

};

std::unordered_map<std::string, GLSharedPtr<GLTexture>> GLTextureLoader::loadedTextures;