#pragma once
#include "Object.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
class imGUIManager
{
public:
    imGUIManager(GLFWwindow* window);
    void Update();
    ~imGUIManager();
    Object* current_item=nullptr;
};
extern imGUIManager* IMGUIMANAGER;
