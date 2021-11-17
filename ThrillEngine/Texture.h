#pragma once
#include <string>
#include "Component.h"
#include "Shader.h"

class Texture : public Component
{
public:
    virtual void Init();
    virtual ~Texture();
    virtual void Update(Shader shader);
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


class CubeMapTexture : public Texture
{
public:
    void Init() override;
    ~CubeMapTexture() override;
    void Update(Shader shader) override;

    void SetTopTexture(const std::string& texture_id);
    void SetBottomTexture(const std::string& texture_id);
    void SetFrontTexture(const std::string& texture_id);
    void SetBackTexture(const std::string& texture_id);
    void SetLeftTexture(const std::string& texture_id);
    void SetRightTexture(const std::string& texture_id);
    void SetTopTexture(int texture_id);
    void SetBottomTexture(int texture_id);
    void SetFrontTexture(int texture_id);
    void SetBackTexture(int texture_id);
    void SetLeftTexture(int texture_id);
    void SetRightTexture(int texture_id);
private:
    int top=-1, bottom=-1, front=-1, back=-1, left=-1, right=-1;
};