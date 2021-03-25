#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include<glm/glm.hpp>

#include "Component.h"

class Texture : public Component
{
public:
    unsigned int LoadTexture(std::string path);
    void Init();
    ~Texture();
private:
    unsigned int texture1, texture2;
    int width, height, nrChannels;
    unsigned char* data;


};

