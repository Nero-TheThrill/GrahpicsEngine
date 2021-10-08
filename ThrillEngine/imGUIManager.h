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
    bool lightNumberChanged = true;
    int lightNumber = 1;
    int prev_lightNumber = 1;
};
extern imGUIManager* IMGUIMANAGER;
