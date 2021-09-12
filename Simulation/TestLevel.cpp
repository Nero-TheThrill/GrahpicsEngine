#include "TestLevel.h"

#include <iostream>
#include "Graphics.h"
#include "Input.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

TestLevel::TestLevel()
{
}

void TestLevel::Init()
{
    obj1 = new Object("light");
    obj1->SetMesh(GRAPHICS->GetMesh("cube"));
    obj1->Pick_Material("MTest");
    obj1->texture.SetTexture("face");
    obj1->SetColor(glm::vec3(1, 1, 1));
    obj1->transform.Translate(glm::vec3(6, 1, 0));
    obj1->transform.Scale(glm::vec3(0.25, 0.25, 0.25));


    obj2 = new Object("object2");
    obj2->SetMesh(GRAPHICS->GetMesh("cube"));
    obj2->Pick_Material("MLight");
    obj2->SetColor(glm::vec3(0.1, 0.3, 0.8));
    obj2->transform.Scale(glm::vec3(1, 1, 1));
    obj2->transform.Translate(glm::vec3(-4, 0, 0));

    obj3 = new Object("object3");
    obj3->SetMesh(GRAPHICS->GetMesh("bunny"));
    obj3->Pick_Material("MLight");
    obj3->transform.Scale(glm::vec3(2, 2, 2));
    obj3->SetColor(glm::vec3(0.812, 0.508, 0.501));

    obj4 = new Object("object4", obj3);
    obj4->SetMesh(GRAPHICS->GetMesh("sphere"));
    obj4->SetColor(glm::vec3(0.512, 0.508, 0.501));
    obj4->transform.Translate(glm::vec3(4, 0, 0));

    obj5 = new Object("object5", obj3);
    obj5->SetMesh(GRAPHICS->GetMesh("lucy_princeton"));
    obj5->SetColor(glm::vec3(0.512, 0.908, 0.501));
    obj5->transform.Translate(glm::vec3(0, -4, 0));

    c1 = new Object("circle1");
    c1->SetMesh(GRAPHICS->GetMesh("sphere"));
    c1->Pick_Material("MLight");
    c1->SetColor(glm::vec3(0.3, 0.3, 0.1));
    c1->transform.Translate(glm::vec3(7, -3, 0));
    c1->transform.Scale(glm::vec3(0.1, 0.1, 0.1));

    c2 = new Object("circle2", c1);
    c2->SetColor(glm::vec3(0.4, 0.9, 0.1));

    c3 = new Object("circle3", c1);
    c3->SetColor(glm::vec3(0.8, 0.3, 0.8));

    c4 = new Object("circle4", c1);
    c4->SetColor(glm::vec3(0.9, 0.7, 0.8));

    c5 = new Object("circle5", c1);
    c5->SetColor(glm::vec3(0.8, 0.3, 0.8));

    c6 = new Object("circle6", c1);
    c6->SetColor(glm::vec3(0.9, 0.8, 0.6));

    c7 = new Object("circle7", c1);
    c7->SetColor(glm::vec3(0.9, 0.7, 0.8));

    c8 = new Object("circle8", c1);
    c8->SetColor(glm::vec3(0.5, 0.8, 0.3));
}

void TestLevel::Update()
{
    GRAPHICS->GetMaterial("MLight")->set("lightPosition", obj1->transform.position);
    GRAPHICS->GetMaterial("MLight")->set("viewPosition", GRAPHICS->camera.cam_position);
    //if (Input::IsTriggered(GLFW_KEY_Z))
    //{
    //    OBJECTMANAGER->DeleteAll();
    //    obj1 = nullptr;
    //    obj2 = nullptr;

    //}
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
      if (obj5 != nullptr)
          obj5->transform.Rotate(TIMEMANAGER->currentFrame * 20.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    if (c1 != nullptr)
        c1->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame) * 5, -3, sin(TIMEMANAGER->currentFrame) * 5));
    if (c2 != nullptr)
        c2->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 0.76f) * 5));
    if (c3 != nullptr)
        c3->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 2 * 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 2 * 0.76f) * 5));
    if (c4 != nullptr)
        c4->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 3 * 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 3 * 0.76f) * 5));
    if (c5 != nullptr)
        c5->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 4 * 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 4 * 0.76f) * 5));
    if (c6 != nullptr)
        c6->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 5 * 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 5 * 0.76f) * 5));
    if (c7 != nullptr)
        c7->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 6 * 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 6 * 0.76f) * 5));
    if (c8 != nullptr)
        c8->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 7 * 0.76f) * 5, -3, sin(TIMEMANAGER->currentFrame + 7 * 0.76f) * 5));
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
        LEVELMANAGER->ChangeLevel(2);
    }
}

void TestLevel::Close()
{
    OBJECTMANAGER->DeleteAll();

}

TestLevel::~TestLevel()
{
}
