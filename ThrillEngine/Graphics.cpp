#include "Graphics.h"
#include<array>
#include <iostream>

Graphics* GRAPHICS = nullptr;

glm::vec3 vertices[] = {
{-0.5f, -0.5f, 0.0f},
{ 0.5f, -0.5f, 0.0f},
 {0.0f,  0.5f, 0.0f}
};

void Graphics::Init()
{
    GRAPHICS = this;
    obj.LoadObject("null");
}

void Graphics::Update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    obj.draw();
}

Graphics::~Graphics()
{
}
