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
    GRAPHICS->SetBackgroundColor(glm::vec4(1));
    obj1 = new Object("object11");
    obj1->SetMesh(GRAPHICS->GetMesh("cube"));
    obj1->Pick_Material("MTest");
    obj1->texture.SetTexture("face");
    obj1->SetColor(glm::vec3(1, 1, 1));
    obj1->transform.Translate(glm::vec3(6, 4, 3));
    obj1->transform.Scale(glm::vec3(0.6, 0.6, 0.6));


    obj2 = new Object("object22");
    obj2->SetMesh(GRAPHICS->GetMesh("customsphere"));
    obj2->Pick_Material("MTexture");
    obj2->texture.SetTexture("moon");
    obj2->transform.Scale(glm::vec3(5, 5, 5));
    obj2->transform.Rotate(-96, glm::vec3(1, 0.19, 0.67));
}

void TestLevel1::Update()
{
    if (obj1 != nullptr)
    {
        GRAPHICS->GetMaterial("MLight")->set("lightPosition", obj1->transform.position);
        GRAPHICS->GetMaterial("MLight")->set("viewPosition", GRAPHICS->camera.cam_position);
        GRAPHICS->GetMaterial("MTexture")->set("lightPosition", obj1->transform.position);
        GRAPHICS->GetMaterial("MTexture")->set("viewPosition", GRAPHICS->camera.cam_position);
        GRAPHICS->SetBackgroundColor(glm::vec4((sin(TIMEMANAGER->currentFrame) + 1.f) / 20.f, (cos(TIMEMANAGER->currentFrame) + 1.f) / 20.f, 0.3, 1));
        glm::vec3 col = glm::vec3{ std::max(std::min(obj1->transform.position.x / 10.f,1.f),0.f),std::max(std::min(obj1->transform.position.y / 10.f,1.f),0.f),std::max(std::min(obj1->transform.position.z / 10.f,1.f),0.f) };
        obj1->SetColor(col);
        GRAPHICS->GetMaterial("MLight")->set("lightColor", col);
        GRAPHICS->GetMaterial("MTexture")->set("lightColor", col);
        if (Input::IsPressed(GLFW_KEY_W))
        {
            obj1->transform.Move(glm::vec3(0, 3, 0));
        }
        if (Input::IsPressed(GLFW_KEY_S))
        {
            obj1->transform.Move(glm::vec3(0, -3, 0));
        }
        if (Input::IsPressed(GLFW_KEY_A))
        {
            obj1->transform.Move(glm::vec3(-3, 0, 0));
        }
        if (Input::IsPressed(GLFW_KEY_D))
        {
            obj1->transform.Move(glm::vec3(3, 0, 0));
        }
        if (Input::IsPressed(GLFW_KEY_Q))
        {
            obj1->transform.Move(glm::vec3(0, 0, -3));
        }
        if (Input::IsPressed(GLFW_KEY_E))
        {
            obj1->transform.Move(glm::vec3(0, 0, 3));
        }
        obj1->transform.Rotate(-(float)glfwGetTime() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    }
    if (Input::IsTriggered(GLFW_KEY_Z))
    {
        OBJECTMANAGER->DeleteAll();
        obj1 = nullptr;
        obj2 = nullptr;
    }
    if (obj2 != nullptr)
        obj2->transform.RotateMove(TIMEMANAGER->deltaTime * 50, glm::vec3(0.0f, 0.0f, 1.0f));
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
    std::cout << "TestLevel1 Destructor Called" << std::endl;
}
