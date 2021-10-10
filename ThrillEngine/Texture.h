#pragma once
#include <string>
#include "Component.h"

class Texture : public Component
{
public:
    void Init();
    ~Texture();
    void Update();
    void SetTexture(const std::string& texture_id);
    int texture = -1;
private:
   
};

