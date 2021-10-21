#include "TestLevel.h"
#include <iostream>
#include "Graphics.h"
#include "Input.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
TestLevel::TestLevel()
{
    orbit = nullptr;
    obj1 = nullptr;
    obj2 = nullptr;
    obj3 = nullptr;
    obj4 = nullptr;
    obj5 = nullptr;

    skysphere = nullptr;
    centerobj = nullptr;
    baron = nullptr;
    penguin = nullptr;
    time_count = 0;
}

void TestLevel::Init()
{
    GRAPHICS->SetBackgroundColor(glm::vec4(0.6,0.65,0.7,1.0));

    orbit = new Object("orbit");
    orbit->SetMeshGroup(GRAPHICS->GetMeshGroup("line"));
    orbit->SetShader("test");
    orbit->SetColor(glm::vec3(1, 1, 1));
    orbit->transform.Translate(glm::vec3(0, -3, 0));
    orbit->transform.Scale(glm::vec3(9, 9, 9));

    //obj1 = new Object("light");
    //obj1->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
    //obj1->SetShader("test");
    //obj1->SetColor(glm::vec3(1, 1, 0.8));
    //obj1->transform.Translate(glm::vec3(8, 5, 4));
    //obj1->transform.Scale(glm::vec3(0.2, 0.2, 0.2));
    //obj1->texture.SetTexture("moon");


    //obj2 = new Object("starwars");
    //obj2->SetMeshGroup(GRAPHICS->GetMeshGroup("starwars"));
    //obj2->SetShader("phong_shading");
    //obj2->transform.Translate(glm::vec3(3.7f, 1.8f, 0.f));
    //obj2->transform.Rotate(35, glm::vec3(1, 1, -1));
    //obj2->transform.Scale(glm::vec3(2.f));
    //obj2->SetColor(glm::vec3(0.21f, 0.42f, 0.39f));

    obj3 = new Object("plane");
    obj3->SetMeshGroup(GRAPHICS->GetMeshGroup("quad"));
    obj3->SetShader("phong_shading");
    obj3->transform.Translate(glm::vec3(0, -7, 0));
    obj3->transform.Rotate(-90, glm::vec3(1, 0, 0));
    obj3->transform.Scale(glm::vec3(10.f));
    obj3->drawmode = 1;


    //obj5 = new Object("sphere from code");
    //obj5->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
    //obj5->SetShader("phong_shading");
    //obj5->transform.Translate(glm::vec3(0, 5, 0));
    //obj5->transform.Rotate(-231, glm::vec3(1, -1, 0.23));
    //obj5->transform.Scale(glm::vec3(3, 3, 3));
    //obj5->texture.SetTexture("earth");
    //obj5->drawmode = 1;


    //baron = new Object("baron");
    //baron->SetMeshGroup(GRAPHICS->GetMeshGroup("baron"));
    //baron->SetShader("phong_shading");
    //baron->transform.Translate(glm::vec3(24.3f, -12.2f, -34.f));
    //baron->transform.Scale(glm::vec3(20.f));
    //baron->texture.SetTexture("baron");
    //baron->transform.Rotate(-42, glm::vec3(0, 1, 0));

    centerobj = new Object("centerobject");
    centerobj->SetMeshGroup(GRAPHICS->GetMeshGroup("cube"));
    centerobj->SetShader("phong_shading");
    centerobj->transform.Translate(glm::vec3(0, -3.f, 0.0f));
    centerobj->transform.Scale(glm::vec3(3.f));
    //centerobj->texture.SetTexture("test");
   // centerobj->transform.Rotate(26, glm::vec3(-1, 0.24, -1));
    centerobj->drawmode = 1;
    GRAPHICS->centerobj = centerobj;

    //penguin = new Object("penguin");
    //penguin->SetMeshGroup(GRAPHICS->GetMeshGroup("penguin"));
    //penguin->SetShader("phong_shading");
    //penguin->transform.Translate(glm::vec3(-24.3f, -12.2f, -34.f));
    //penguin->transform.Scale(glm::vec3(10.f));
    //penguin->texture.SetTexture("penguin");
    //penguin->transform.Rotate(77, glm::vec3(0, 1, 0));

    //skysphere = new Object("skysphere");
    //skysphere->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
    //skysphere->SetShader("phong_shading");
    //skysphere->transform.Scale(glm::vec3(50, 50, 50));
    //skysphere->texture.SetTexture("space");
    //skysphere->drawmode = 1;

    IMGUIMANAGER->Init();
}

void TestLevel::Update()
{
    if (obj1 != nullptr)
    {
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
    }
    if (obj5 != nullptr)
        obj5->transform.RotateMove(TIMEMANAGER->deltaTime * 50, glm::vec3(0.0f, 0.0f, 1.0f));
    if (IMGUIMANAGER->lightNumberChanged)
    {
        for (auto light : lights)
        {
            light->alive = false;
        }
        lights.clear();
        for (int i = 0; i < IMGUIMANAGER->lightNumber; i++)
        {
            LightObject* lightsource = new LightObject("light" + std::to_string(i));
            lightsource->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
            lightsource->SetShader("light");
            lightsource->transform.Scale(glm::vec3(0.2, 0.2, 0.2));
            lightsource->drawmode = 1;
            lightsource->type = LightType::POINT;
            lights.push_back(lightsource);
        }
        for (int i = 0; i < lights.size(); i++)
        {
            lights[i]->transform.Translate(glm::vec3(cos(time_count + (float)i * 6.28f / lights.size()) * 9, -3, sin(time_count + (float)i * 6.28f / lights.size()) * 9));
        }
        IMGUIMANAGER->lightNumberChanged = false;
    }
    if (IMGUIMANAGER->shouldRotatelight)
    {
        time_count += TIMEMANAGER->deltaTime;
        for (int i = 0; i < lights.size(); i++)
        {
            lights[i]->transform.Translate(glm::vec3(cos(time_count + (float)i * 6.28f / lights.size()) * 9, -3, sin(time_count + (float)i * 6.28f / lights.size()) * 9));
        }
    }
    if (centerobj != nullptr)
    {
      //  centerobj->transform.RotateMove(TIMEMANAGER->deltaTime * 6, glm::vec3(0, 1, 0));
    }
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
        GRAPHICS->camera.RotateYaxis(0.3f);
    }
    if (Input::IsPressed(GLFW_KEY_U))
    {
        GRAPHICS->camera.RotateYaxis(-0.3f);
    }
    if (Input::IsPressed(GLFW_KEY_SEMICOLON))
    {
        GRAPHICS->camera.RotateXaxis(0.3f);
    }
    if (Input::IsPressed(GLFW_KEY_P))
    {
        GRAPHICS->camera.RotateXaxis(-0.3f);
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
