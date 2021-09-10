#include "TimeManager.h"
#include <iostream>
#include <GLFW/glfw3.h>

TimeManager* TIMEMANAGER = nullptr;

TimeManager::TimeManager()
{
    TIMEMANAGER = this;
    std::cout << "TimeSystem Initialize" << std::endl;
    currentFrame = 0;
    deltaTime = 0;
    lastFrame = 0;
}

void TimeManager::Init()
{

}

void TimeManager::Update()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

TimeManager::~TimeManager()
{
}
