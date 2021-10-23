#include "Texture.h"
#include "Graphics.h"

void Texture::Init()
{
}

Texture::~Texture()
{
}

void Texture::Update(Shader shader)
{
    if (texture != -1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        shader.set("default_texture", 0);
    }
    if (ambient_texture != -1)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, ambient_texture);
        shader.set("ambient_texture", 1);
    }
    if (diffuse_texture != -1)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, diffuse_texture);
        shader.set("diffuse_texture", 2);
    }
    if (specular_texture != -1)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, specular_texture);
        shader.set("specular_texture", 3);
    }
    shader.set("default_texture_exists", texture != -1);
    shader.set("ambient_texture_exists", ambient_texture != -1);
    shader.set("diffuse_texture_exists", diffuse_texture != -1);
    shader.set("specular_texture_exists", specular_texture != -1);
}

void Texture::SetTexture(const std::string& texture_id)
{
    texture = GRAPHICS->GetTexture(texture_id);
}

void Texture::SetAmbientTexture(const std::string& texture_id)
{
    ambient_texture = GRAPHICS->GetTexture(texture_id);
}

void Texture::SetDiffuseTexture(const std::string& texture_id)
{
    diffuse_texture = GRAPHICS->GetTexture(texture_id);
}

void Texture::SetSpecularTexture(const std::string& texture_id)
{
    specular_texture = GRAPHICS->GetTexture(texture_id);
}
