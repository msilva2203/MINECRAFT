#pragma once
#include <string>

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

private:
    unsigned int RendererID;
    std::string FilePath;
    unsigned char* LocalBuffer;
    int Width, Height, Pixels;
};
