#include "TestLevel.h"

#include <iostream>


#include "Input.h"
#include "ObjectManager.h"

TestLevel::TestLevel()
{
}

void TestLevel::Init()
{
    obj1 = new Object();
    obj1->pick_shader("texture");
    obj1->texture.SetTexture("face");
    obj1->transform.Translate(glm::vec3(0.8,0.7,1.5f));
    obj1->transform.Scale(glm::vec3(0.3, 0.3, 0.3));


    obj2 = new Object();
    obj2->pick_shader("texture");
    obj2->texture.SetTexture("container");
    obj2->SetColor(glm::vec4(0, 1, 1, 1));
    obj2->transform.Scale(glm::vec3(0.7, 0.7, 0.7));


}

void TestLevel::Update()
{
    if (Input::IsTriggered(GLFW_KEY_1))
    {
        OBJECTMANAGER->DeleteAll();
        obj1 = nullptr;
        obj2 = nullptr;
    }
    if (Input::IsPressed(GLFW_KEY_W))
    {
        obj1->transform.Move(glm::vec3(0, 0.01f, 0));
    }
    if (Input::IsPressed(GLFW_KEY_S))
    {
        obj1->transform.Move(glm::vec3(0, -0.01f, 0));
    }
    if (Input::IsPressed(GLFW_KEY_A))
    {
        obj1->transform.Move(glm::vec3(-0.01f, 0, 0));
    }
    if (Input::IsPressed(GLFW_KEY_D))
    {
        obj1->transform.Move(glm::vec3(0.01f, 0, 0));
    }
    if (Input::IsPressed(GLFW_KEY_Q))
    {
        obj1->transform.Move(glm::vec3(0, 0, -0.01f));
    }
    if (Input::IsPressed(GLFW_KEY_E))
    {
        obj1->transform.Move(glm::vec3(0, 0, 0.01f));
    }
    if(obj1!=nullptr)
        obj1->transform.Rotate(-(float)glfwGetTime() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    if(obj2!=nullptr)
        obj2->transform.Rotate((float)glfwGetTime() * 150.0f, glm::vec3(0.5f, 1.0f, 0.0f));

}

void TestLevel::Close()
{
}

TestLevel::~TestLevel()
{
}
