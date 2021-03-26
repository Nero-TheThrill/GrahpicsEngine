#include "Texture.h"
#include "Graphics.h"



void Texture::Init()
{
}




Texture::~Texture()
{
}

void Texture::Update()
{
    glBindTextureUnit(0, texture);
}

void Texture::SetTexture(const std::string& texture_id)
{
    texture = GRAPHICS->GetTexture(texture_id);
}
