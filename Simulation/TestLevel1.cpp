#include "TestLevel1.h"
#include <iostream>
#include "Graphics.h"
#include "Input.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

TestLevel1::TestLevel1()
{
}

void TestLevel1::Init()
{
    obj1 = new Object("lv1obj1");
    obj1->pick_material("MTest");
    obj1->texture.SetTexture("face");
    obj1->SetColor(glm::vec3(1, 1, 1));
    obj1->transform.Translate(glm::vec3(1.5, 1.5, 0));
    obj1->transform.Scale(glm::vec3(1, 1, 1));


    obj2 = new Object("lv1obj2");
    obj2->pick_material("MTexture");
    obj2->texture.SetTexture("container");
    obj2->SetColor(glm::vec3(0.1, 0.3, 0.8));
    obj2->transform.Scale(glm::vec3(1, 1, 1));

}

void TestLevel1::Update()
{
    obj1->SetColor(glm::vec3{ 0.5 } + obj1->transform.position);
    if (Input::IsTriggered(GLFW_KEY_Z))
    {
        OBJECTMANAGER->DeleteAll();
        obj1 = nullptr;
        obj2 = nullptr;
    }
    if (Input::IsPressed(GLFW_KEY_W))
    {
        obj1->transform.Move(glm::vec3(0, 1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_S))
    {
        obj1->transform.Move(glm::vec3(0, -1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_A))
    {
        obj1->transform.Move(glm::vec3(-1, 0, 0));
    }
    if (Input::IsPressed(GLFW_KEY_D))
    {
        obj1->transform.Move(glm::vec3(1, 0, 0));
    }
    if (Input::IsPressed(GLFW_KEY_Q))
    {
        obj1->transform.Move(glm::vec3(0, 0, -1));
    }
    if (Input::IsPressed(GLFW_KEY_E))
    {
        obj1->transform.Move(glm::vec3(0, 0, 1));
    }
    if (obj1 != nullptr)
        obj1->transform.Rotate(-(float)glfwGetTime() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    if (obj2 != nullptr)
        obj2->transform.Rotate((float)glfwGetTime() * 150.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    if (Input::IsPressed(GLFW_KEY_UP))
    {
        GRAPHICS->camera.Move(glm::vec3(0, 1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_DOWN))
    {
        GRAPHICS->camera.Move(glm::vec3(0, -1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_RIGHT))
    {
        GRAPHICS->camera.Move(glm::vec3(1, 0, 0));
    }
    if (Input::IsPressed(GLFW_KEY_LEFT))
    {
        GRAPHICS->camera.Move(glm::vec3(-1, 0, 0));
    }
    if (Input::IsPressed(GLFW_KEY_KP_1))
    {
        GRAPHICS->camera.Move(glm::vec3(0, 0, 1));
    }
    if (Input::IsPressed(GLFW_KEY_KP_2))
    {
        GRAPHICS->camera.Move(glm::vec3(0, 0, -1));
    }
    if (Input::IsTriggered(GLFW_KEY_N))
    {
        Close();
        LEVELMANAGER->ChangeLevel(1);
    }

}

void TestLevel1::Close()
{
    OBJECTMANAGER->DeleteAll();
}

TestLevel1::~TestLevel1()
{
}
