#include "Rendering/Texture.h"

#include <GL/glew.h>

#include "Rendering/Renderer.h"
#include "stb/stb_image.h"

Texture::Texture(const std::string& filepath) :
    RendererID(0),
    FilePath(filepath),
    LocalBuffer(nullptr),
    Width(0),
    Height(0),
    Pixels(0)
{
    stbi_set_flip_vertically_on_load(1);
    LocalBuffer = stbi_load(filepath.c_str(), &Width, &Height, &Pixels, 4);
    
    glCall(glGenTextures(1, &RendererID))
    glCall(glBindTexture(GL_TEXTURE_2D, RendererID))

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST))
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST))
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer))
    glCall(glBindTexture(GL_TEXTURE_2D, 0))

    if (LocalBuffer)
        stbi_image_free(LocalBuffer);
}

Texture::~Texture()
{
    glCall(glDeleteTextures(1, &RendererID))
}

void Texture::Bind(unsigned int slot) const
{
    glCall(glActiveTexture(GL_TEXTURE0 + slot))
    glCall(glBindTexture(GL_TEXTURE_2D, RendererID))
}

void Texture::Unbind() const
{
    glCall(glBindTexture(GL_TEXTURE_2D, 0))
}
