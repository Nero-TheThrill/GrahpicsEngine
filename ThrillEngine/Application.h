#pragma once
#include "headers.h"
#include "EngineCore.h"


class Application : public EngineCore
{
public:
    Application() = default;
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
    int width=800, height=600, prevwidth, prevheight;
    int xpos, ypos;
    bool IsFullScreen;
};
extern Application* APPLICATION;


