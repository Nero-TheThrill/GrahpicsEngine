#pragma once
#include "headers.h"
#include "EngineCore.h"
#include "imGUIManager.h"


class Application : public EngineCore
{
public:
    Application();
    void AppSet(int w, int h);
    void Init() override;
    void Update() override;
    ~Application() override;

    bool shouldClose() const;

    glm::vec2 GetWindowSize() const;
    void SetWindowSize(int w, int h);

    void SetFullScreen();
private:
    GLFWwindow* window;
    GLFWmonitor* monitor;
    int width = 800, height = 600, prevwidth, prevheight;
    int xpos, ypos;
    bool IsFullScreen;
    bool show_demo_window = false, show_another_window = false;
    glm::vec3 clear_color = glm::vec3{ 1.0 };
    int counter = 0;
    imGUIManager* imGUI_;

};
extern Application* APPLICATION;


