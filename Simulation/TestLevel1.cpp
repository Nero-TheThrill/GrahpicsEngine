#include "TestLevel1.h"
#include <iostream>
#include "Graphics.h"
#include "Input.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"


TestLevel1::TestLevel1()
{
    obj1 = nullptr;
    obj2 = nullptr;
    obj3 = nullptr;
}

void TestLevel1::Init()
{
    GRAPHICS->SetBackgroundColor(glm::vec4(1));
    obj1 = new Object("object11");
    obj1->SetMeshGroup(GRAPHICS->GetMeshGroup("cube"));
    obj1->SetShader("test");
    obj1->SetColor(glm::vec3(1, 1, 1));
    obj1->transform.Translate(glm::vec3(6, 4, 3));
    obj1->transform.Scale(glm::vec3(0.6, 0.6, 0.6));


    obj2 = new Object("object22");
    obj2->SetMeshGroup(GRAPHICS->GetMeshGroup("ramus"));
    obj2->SetShader("texture");
    obj2->texture.SetTexture("ramus");
    obj2->transform.Scale(glm::vec3(5, 5, 5));
    obj2->transform.Rotate(26, glm::vec3(-1, 0.24, -1));

    GRAPHICS->SetLightObject(obj1);
}

void TestLevel1::Update()
{
    if (obj1 != nullptr)
    {
        GRAPHICS->SetBackgroundColor(glm::vec4((sin(TIMEMANAGER->currentFrame) + 1.f) / 20.f, (cos(TIMEMANAGER->currentFrame) + 1.f) / 20.f, 0.3, 1));
        glm::vec3 col = glm::vec3{ std::max(std::min(obj1->transform.position.x / 10.f,1.f),0.f),std::max(std::min(obj1->transform.position.y / 10.f,1.f),0.f),std::max(std::min(obj1->transform.position.z / 10.f,1.f),0.f) };
        obj1->SetColor(col);
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
        obj2->transform.RotateMove(TIMEMANAGER->deltaTime * 50, glm::vec3(0.0f, 1.0f, 0.0f));
    if (Input::IsPressed(GLFW_KEY_Y))
    {
        GRAPHICS->camera.Move(glm::vec3(0, 1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_H))
    {
        GRAPHICS->camera.Move(glm::vec3(0, -1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_L))
    {
        GRAPHICS->camera.MoveSide(2);
    }
    if (Input::IsPressed(GLFW_KEY_J))
    {
        GRAPHICS->camera.MoveSide(-2);
    }
    if (Input::IsPressed(GLFW_KEY_I))
    {
        GRAPHICS->camera.MoveForward(2);
    }
    if (Input::IsPressed(GLFW_KEY_K))
    {
        GRAPHICS->camera.MoveForward(-2);
    }
    if (Input::IsPressed(GLFW_KEY_O))
    {
        GRAPHICS->camera.RotateYaxis(0.5f);
    }
    if (Input::IsPressed(GLFW_KEY_U))
    {
        GRAPHICS->camera.RotateYaxis(-0.5f);
    }
    if (Input::IsPressed(GLFW_KEY_SEMICOLON))
    {
        GRAPHICS->camera.RotateXaxis(0.5f);
    }
    if (Input::IsPressed(GLFW_KEY_P))
    {
        GRAPHICS->camera.RotateXaxis(-0.5f);
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
