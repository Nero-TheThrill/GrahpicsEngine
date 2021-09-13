#include "Application.h"
#include <iostream>
#include "Input.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key<0 || key>GLFW_KEY_LAST)
        return;
    Input::SetKeyboard(static_cast<KEY_STATE>(action), key);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::SetKeyboard(static_cast<KEY_STATE>(action), button);
}
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    Input::SetMousePosition(static_cast<float>(xpos), static_cast<float>(ypos));
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::SetScroll(static_cast<float>(yoffset));
}
void window_size_callback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
    APPLICATION->SetWindowSize(w, h);
}
Application* APPLICATION = nullptr;

Application::Application()
{
    APPLICATION = this;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    std::cout << "Application Initialize" << std::endl;

    imGUI_ = new imGUIManager(window);
}

void Application::AppSet(int w, int h)
{
    width = w;
    height = h;
    glfwSetWindowSize(window, w, h);
}

void Application::Init()
{

}



void Application::Update()
{

    IMGUIMANAGER->Update();
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (Input::IsTriggered(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
    if (Input::IsTriggered(GLFW_KEY_F))
        SetFullScreen();

}

Application::~Application()
{
    std::cout << "delete Application" << std::endl;

    glfwTerminate();
}

bool Application::shouldClose() const
{
    return !glfwWindowShouldClose(window);
}

glm::vec2 Application::GetWindowSize() const
{
    return glm::vec2{ width,height };
}

void Application::SetWindowSize(int w, int h)
{
    width = w;
    height = h;
}

void Application::SetFullScreen()
{
    if (!IsFullScreen)
    {
        glfwGetWindowPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &prevwidth, &prevheight);
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
        window_size_callback(window, mode->width, mode->height);
        glfwSwapInterval(1);
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, xpos, ypos, prevwidth, prevheight, 0);
        glfwSwapInterval(1);
    }
    IsFullScreen = !IsFullScreen;
}

