#pragma once
#include <string>
#include "Component.h"
#include "Shader.h"

class Texture : public Component
{
public:
    void Init();
    ~Texture();
    void Update(Shader shader);
    void SetTexture(const std::string& texture_id);
    void SetAmbientTexture(const std::string& texture_id);
    void SetDiffuseTexture(const std::string& texture_id);
    void SetSpecularTexture(const std::string& texture_id);
    int texture = -1;
    int ambient_texture = -1;
    int diffuse_texture = -1;
    int specular_texture = -1;
private:
   
};


//class CubeMapTexture : public Texture
//{
//private:
//    std::vector< Texture2D*>   m_cubeMapTextures;
//};