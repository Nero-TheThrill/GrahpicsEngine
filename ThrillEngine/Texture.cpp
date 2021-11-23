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

void Texture::SetTexture(int texture_id)
{
    texture = texture_id;
}

void Texture::SetAmbientTexture(int texture_id)
{
    ambient_texture = texture_id;
}

void Texture::SetDiffuseTexture(int texture_id)
{
    diffuse_texture = texture_id;
}

void Texture::SetSpecularTexture(int texture_id)
{
    specular_texture = texture_id;
}


void CubeMapTexture::Init()
{

}

CubeMapTexture::~CubeMapTexture()
{
}

void CubeMapTexture::Update(Shader shader)
{
    if (top != -1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, top);
        shader.set("top", 0);
    }
    if (bottom != -1)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, bottom);
        shader.set("bottom", 1);
    }
    if (left != -1)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, left);
        shader.set("left", 2);
    }
    if (right != -1)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, right);
        shader.set("right", 3);
    }
    if (front != -1)
    {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, front);
        shader.set("front", 4);
    }
    if (back != -1)
    {
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, back);
        shader.set("back", 5);
    }
    if (emissive_texture != -1)
    {
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, emissive_texture);
        shader.set("emissive_texture", 6);
    }
    shader.set("emissive_texture_exists", emissive_texture != -1);
}

void CubeMapTexture::SetTopTexture(const std::string& texture_id)
{
    top = GRAPHICS->GetTexture(texture_id);
}

void CubeMapTexture::SetBottomTexture(const std::string& texture_id)
{
    bottom = GRAPHICS->GetTexture(texture_id);
}

void CubeMapTexture::SetFrontTexture(const std::string& texture_id)
{
    front = GRAPHICS->GetTexture(texture_id);
}

void CubeMapTexture::SetBackTexture(const std::string& texture_id)
{
    back = GRAPHICS->GetTexture(texture_id);
}

void CubeMapTexture::SetLeftTexture(const std::string& texture_id)
{
    left = GRAPHICS->GetTexture(texture_id);
}

void CubeMapTexture::SetRightTexture(const std::string& texture_id)
{
    right = GRAPHICS->GetTexture(texture_id);
}

void CubeMapTexture::SetTopTexture(int texture_id)
{
    top = texture_id;
}

void CubeMapTexture::SetBottomTexture(int texture_id)
{
    bottom = texture_id;
}

void CubeMapTexture::SetFrontTexture(int texture_id)
{
    front = texture_id;
}

void CubeMapTexture::SetBackTexture(int texture_id)
{
    back = texture_id;
}

void CubeMapTexture::SetLeftTexture(int texture_id)
{
    left = texture_id;
}

void CubeMapTexture::SetRightTexture(int texture_id)
{
    right = texture_id;
}

void CubeMapTexture::SetEmissiveTexture(const std::string& texture_id)
{
    emissive_texture = GRAPHICS->GetTexture(texture_id);
}
