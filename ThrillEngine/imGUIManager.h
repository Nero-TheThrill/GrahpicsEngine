#pragma once
#include "LightObject.h"
#include "Object.h"
#include "imgui/imgui_impl_glfw.h"
class imGUIManager
{
public:
    imGUIManager(GLFWwindow* window);
    void Update();
    void Init();
    ~imGUIManager();
    Object* current_item = nullptr,*prev_item=nullptr;
    LightObject* current_light = nullptr;
    bool shouldRotatelight = true;
    bool lightNumberChanged = true;
    int lightNumber = 1;
    int prev_lightNumber = 1;
    std::string light_type[3];
};
extern imGUIManager* IMGUIMANAGER;
