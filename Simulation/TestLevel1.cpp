#include "TestLevel1.h"
#include <iostream>
#include "Graphics.h"
#include "Input.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
TestLevel1::TestLevel1()
{
    plane = nullptr;
    centerobj = nullptr;
    obj = nullptr;
    time_count = 0;

    dragon = nullptr;
}

void TestLevel1::Init()
{
    IMGUIMANAGER->useIMGUI = false;
    time_count = 0;
    GRAPHICS->SetBackgroundColor(glm::vec4(0.6, 0.65, 0.7, 1.0));
    
    
    plane = new Object("plane");
    plane->SetMeshGroup(GRAPHICS->GetMeshGroup("quad"));
    plane->SetShader("phong_shading");
    plane->material = GRAPHICS->GetMaterial("m_default");
    plane->transform.Translate(glm::vec3(0, -7, 0));
    plane->transform.Rotate(-90, glm::vec3(1, 0, 0));
    plane->transform.Scale(glm::vec3(20.f));
    plane->drawmode = 1;


    centerobj = new Object("centerobject");
    centerobj->SetMeshGroup(GRAPHICS->GetMeshGroup("dolphin"));
    centerobj->SetShader("phong_shading_cube");
    centerobj->material = GRAPHICS->GetMaterial("m_environment");
    centerobj->transform.Translate(glm::vec3(0.f, 0.f, 0.f));
    centerobj->transform.Scale(glm::vec3(8.f));
    centerobj->transform.Rotate(-97, glm::vec3(0.66f, 0.27f, 0.23f));
    centerobj->drawmode = 1;
    centerobj->environmentmapping_mode = 0;
    centerobj->isUsingCubeMapTexture = true;
    centerobj->isModePhongShading_EnvironmentMapping = true;
    centerobj->mixRate = 0.9f;
    GRAPHICS->centerobj = centerobj;








    for (int i = 0; i < 8; i++)
    {
        LightObject* lightsource = new LightObject("light" + std::to_string(i));
        lightsource->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
        lightsource->SetShader("light");
        lightsource->transform.Scale(glm::vec3(0.2, 0.2f, 0.2));
        lightsource->drawmode = 1;
        lightsource->type = LightType::SPOT;
        lightsource->material = GRAPHICS->GetMaterial("m_light");
        lightsource->inner_angle = 0.29f;
        lightsource->outer_angle = 0.3f;
        lightsource->falloff = 0.001f;
        lights.push_back(lightsource);
    }
    int iter = 0;
    for (auto light : lights)
    {
        if (iter % 8 == 7)
        {
            light->ambient = glm::vec3(1.f, 0.1f, 0.1f)/3.f;
            light->diffuse = glm::vec3(1.f, 0.1f, 0.1f) / 3.f;
            light->specular = glm::vec3(1.f, 0.1f, 0.1f) / 3.f;
        }
        else if (iter % 8 == 6)
        {
            light->ambient = glm::vec3(1.f, 0.5f, 0.1f) / 3.f;
            light->diffuse = glm::vec3(1.f, 0.5f, 0.1f) / 3.f;
            light->specular = glm::vec3(1.f, 0.5f, 0.1f) / 3.f;
        }
        else if (iter % 8 == 5)
        {
            light->ambient = glm::vec3(0.5f, 0.5f, 0.1f) / 3.f;
            light->diffuse = glm::vec3(0.5f, 0.5f, 0.1f) / 3.f;
            light->specular = glm::vec3(0.5f, 0.5f, 0.1f) / 3.f;
        }
        else if (iter % 8 == 4)
        {
            light->ambient = glm::vec3(0.1f, 1.f, 0.1f) / 3.f;
            light->diffuse = glm::vec3(0.1f, 1.f, 0.1f) / 3.f;
            light->specular = glm::vec3(0.1f, 1.f, 0.1f) / 3.f;
        }
        else if (iter % 8 == 3)
        {
            light->ambient = glm::vec3(0.1f, 0.1f, 1.f)/3.f;
            light->diffuse = glm::vec3(0.1f, 0.1f, 1.f)/3.f;
            light->specular = glm::vec3(0.1f, 0.1f, 1.f) / 3.f;
        }
        else if (iter % 8 == 2)
        {
            light->ambient = glm::vec3(0.1f, 0.1f, 0.6f)/3.f;
            light->diffuse = glm::vec3(0.1f, 0.1f, 0.6f)/3.f;
            light->specular = glm::vec3(0.1f, 0.1f, 0.6f) / 3.f;
        }
        else if (iter % 8 == 1)
        {
            light->ambient = glm::vec3(0.6f, 0.1f, 1.f)/3.f;
            light->diffuse = glm::vec3(0.6f, 0.1f, 1.f)/3.f;
            light->specular = glm::vec3(0.6f, 0.1f, 1.f) / 3.f;
        }
        else
        {
            light->ambient = glm::vec3(1.f, 1.f, 1.f)/3.f;
            light->diffuse = glm::vec3(1.f, 1.f, 1.f)/3.f;
            light->specular = glm::vec3(1.f, 1.f, 1.f) / 3.f;
        }
        iter++;
    }

    GRAPHICS->camera.View(glm::vec3(0.0f, 4.0f, 25));
    GRAPHICS->camera.SetPitch(-10);
    GRAPHICS->camera.SetYaw(-90);
    IMGUIMANAGER->Init();
}

void TestLevel1::Update()
{
    time_count += TIMEMANAGER->deltaTime;
    for (int i = 0; i < lights.size(); i++)
    {
        lights[i]->transform.Translate(glm::vec3(cos(time_count + (float)i * 6.28f / lights.size()) * 15, 10, sin(time_count + (float)i * 6.28f / lights.size()) * 15));
    }
    if (obj != nullptr)
    {
        obj->transform.Rotate(TIMEMANAGER->deltaTime, glm::vec3(0, 1, 0));
    }

    if (Input::IsPressed(GLFW_KEY_Q))
    {
        GRAPHICS->camera.Move(glm::vec3(0, 2, 0));
    }
    if (Input::IsPressed(GLFW_KEY_E))
    {
        GRAPHICS->camera.Move(glm::vec3(0, -2, 0));
    }
    if (Input::IsPressed(GLFW_KEY_D))
    {
        GRAPHICS->camera.MoveSide(5);
    }
    if (Input::IsPressed(GLFW_KEY_A))
    {
        GRAPHICS->camera.MoveSide(-5);
    }
    if (Input::IsPressed(GLFW_KEY_W))
    {
        GRAPHICS->camera.MoveForward(5);
    }
    if (Input::IsPressed(GLFW_KEY_S))
    {
        GRAPHICS->camera.MoveForward(-5);
    }
    if (Input::IsPressed(GLFW_KEY_RIGHT))
    {
        GRAPHICS->camera.RotateYaxis(3 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsPressed(GLFW_KEY_LEFT))
    {
        GRAPHICS->camera.RotateYaxis(-3 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsPressed(GLFW_KEY_DOWN))
    {
        GRAPHICS->camera.RotateXaxis(3 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsPressed(GLFW_KEY_UP))
    {
        GRAPHICS->camera.RotateXaxis(-3 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsTriggered(GLFW_KEY_N))
    {
        Close();
        LEVELMANAGER->ChangeLevel(1);
    }
}

void TestLevel1::Close()
{
    lights.clear();
    OBJECTMANAGER->DeleteAll();

}

TestLevel1::~TestLevel1()
{
    std::cout << "TestLevel Destructor Called" << std::endl;
}
