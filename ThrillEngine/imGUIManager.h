#pragma once
#include "Object.h"
#include "imgui/imgui_impl_glfw.h"
class imGUIManager
{
public:
    imGUIManager(GLFWwindow* window);
    void Update();
    ~imGUIManager();
    Object* current_item = nullptr;
    bool shouldRotatelight = true;
};
extern imGUIManager* IMGUIMANAGER;
