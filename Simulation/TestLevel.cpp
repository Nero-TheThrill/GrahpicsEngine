#include "TestLevel.h"
#include <iostream>
#include "Graphics.h"
#include "Input.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

TestLevel::TestLevel()
{
    obj1 = nullptr;
    obj2 = nullptr;
    obj3 = nullptr;
    obj4 = nullptr;
    obj5 = nullptr;
    c1 = nullptr;
    c2 = nullptr;
    c3 = nullptr;
    c4 = nullptr;
    c5 = nullptr;
    c6 = nullptr;
    c7 = nullptr;
    c8 = nullptr;
}

void TestLevel::Init()
{
    orbit = new Object("orbit");
    orbit->SetMesh(GRAPHICS->GetMesh("line"));
    orbit->Pick_Material("MTest");
    orbit->SetColor(glm::vec3(1, 1, 1));
    orbit->transform.Translate(glm::vec3(0, -3, 0));
    orbit->transform.Scale(glm::vec3(9,9,9));

    obj1 = new Object("light");
    obj1->SetMesh(GRAPHICS->GetMesh("customsphere"));
    obj1->Pick_Material("MTest");
    obj1->SetColor(glm::vec3(1, 1, 0.8));
    obj1->transform.Translate(glm::vec3(-5, 4, 8));
    obj1->transform.Scale(glm::vec3(0.2, 0.2, 0.2));
    obj1->texture.SetTexture("moon");


    obj2 = new Object("statue");
    obj2->SetMesh(GRAPHICS->GetMesh("lucy_princeton"));
    obj2->Pick_Material("MLight");
    obj2->SetColor(glm::vec3(0.1, 0.3, 0.8));
    obj2->transform.Translate(glm::vec3(1.6f, 0.4f, 1.2f));
    obj2->transform.Rotate(36,glm::vec3(1,1,-1));

    obj3 = new Object("rabbit");
    obj3->SetMesh(GRAPHICS->GetMesh("bunny_high_poly"));
    obj3->Pick_Material("MLight");
    obj3->transform.Translate(glm::vec3(-0.2f, 0.8f, 0.0f));
    obj3->SetColor(glm::vec3(0.812, 0.508, 0.501));

    obj4 = new Object("sphere loaded from file", obj3);
    obj4->SetMesh(GRAPHICS->GetMesh("sphere"));
    obj4->SetColor(glm::vec3(0.512, 0.508, 0.501));
    obj4->transform.Translate(glm::vec3(9, 5, 0));

    obj5 = new Object("sphere from code");
    obj5->SetMesh(GRAPHICS->GetMesh("customsphere"));
    obj5->Pick_Material("MTexture");
    obj5->transform.Translate(glm::vec3(0, -3, 0));
    obj5->transform.Rotate(-96, glm::vec3(1, 0.19, 0.67));
    obj5->transform.Scale(glm::vec3(3, 3, 3));
    obj5->texture.SetTexture("earth");

    c1 = new Object("orbit_circle1");
    c1->SetMesh(GRAPHICS->GetMesh("customsphere"));
    c1->Pick_Material("MLight");
    c1->SetColor(glm::vec3(0.3, 0.3, 0.1));
    c1->transform.Translate(glm::vec3(7, -3, 0));
    c1->transform.Scale(glm::vec3(0.2, 0.2, 0.2));

    c2 = new Object("orbit_circle2", c1);
    c2->SetColor(glm::vec3(0.4, 0.9, 0.1));

    c3 = new Object("orbit_circle3", c1);
    c3->SetColor(glm::vec3(0.8, 0.3, 0.8));

    c4 = new Object("orbit_circle4", c1);
    c4->SetColor(glm::vec3(0.9, 0.7, 0.8));

    c5 = new Object("orbit_circle5", c1);
    c5->SetColor(glm::vec3(0.8, 0.3, 0.8));

    c6 = new Object("orbit_circle6", c1);
    c6->SetColor(glm::vec3(0.9, 0.8, 0.6));

    c7 = new Object("orbit_circle7", c1);
    c7->SetColor(glm::vec3(0.9, 0.7, 0.8));

    c8 = new Object("orbit_circle8", c1);
    c8->SetColor(glm::vec3(1,1,1));
    c8->Pick_Material("MTexture");
    c8->texture.SetTexture("moon");
    c8->transform.Scale(glm::vec3(0.5, 0.5, 0.5));
    c8->transform.Rotate(-90, glm::vec3(1, 0, 0));
}

void TestLevel::Update()
{
    GRAPHICS->GetMaterial("MLight")->set("lightPosition", obj1->transform.position);
    GRAPHICS->GetMaterial("MLight")->set("viewPosition", GRAPHICS->camera.cam_position);
    GRAPHICS->GetMaterial("MTexture")->set("lightPosition", obj1->transform.position);
    GRAPHICS->GetMaterial("MTexture")->set("viewPosition", GRAPHICS->camera.cam_position);
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
    if (c8 != nullptr)
        c8->transform.RotateMove(TIMEMANAGER->deltaTime * 40, glm::vec3(0.0f, 0.0f, 1.0f));
    if (obj5 != nullptr)
        obj5->transform.RotateMove(TIMEMANAGER->deltaTime * 50, glm::vec3(0.0f, 0.0f, 1.0f));
    if (c1 != nullptr)
        c1->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame) * 9, -3, sin(TIMEMANAGER->currentFrame) * 9));
    if (c2 != nullptr)
        c2->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 0.76f) * 9));
    if (c3 != nullptr)
        c3->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 2 * 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 2 * 0.76f) * 9));
    if (c4 != nullptr)
        c4->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 3 * 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 3 * 0.76f) * 9));
    if (c5 != nullptr)
        c5->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 4 * 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 4 * 0.76f) * 9));
    if (c6 != nullptr)
        c6->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 5 * 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 5 * 0.76f) * 9));
    if (c7 != nullptr)
        c7->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 6 * 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 6 * 0.76f) * 9));
    if (c8 != nullptr)
        c8->transform.Translate(glm::vec3(cos(TIMEMANAGER->currentFrame + 7 * 0.76f) * 9, -3, sin(TIMEMANAGER->currentFrame + 7 * 0.76f) * 9));
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
    std::cout << "TestLevel Destructor Called" << std::endl;
}
