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
    plane = nullptr;
    skysphere = nullptr;
    centerobj = nullptr;
    obj = nullptr;
    ramus = nullptr;
    time_count = 0;

    reflectivedolpihne = nullptr;

    grass = nullptr;

    jet1 = nullptr;
    jet2 = nullptr;
    jet3 = nullptr;

}

void TestLevel::Init()
{
    IMGUIMANAGER->useIMGUI = true;
    GRAPHICS->SetBackgroundColor(glm::vec4(0.6,0.65,0.7,1.0));
    

    ramus = new Object("dolphin");
    ramus->SetMeshGroup(GRAPHICS->GetMeshGroup("ramus"));
    ramus->SetShader("phong_shading");
    ramus->transform.Translate(glm::vec3(-14.8f, -1.2f, -16.5f));
    ramus->transform.Scale(glm::vec3(10.f));
    ramus->transform.Rotate(54, glm::vec3(0, 1, 0));
    ramus->drawmode = 1;

    //grass = new Object("grass");
    //grass->SetMeshGroup(GRAPHICS->GetMeshGroup("grass"));
    //grass->material=GRAPHICS->GetMaterial("m_ground");
    //grass->SetShader("phong_shading");
    //grass->transform.Translate(glm::vec3(0, 8, -53));
    //grass->transform.Scale(glm::vec3(1000,100,1000));
    //grass->transform.Rotate(62, glm::vec3(0, 1, 0));
    //grass->drawmode = 1;

    reflectivedolpihne = new Object("reflective dolphin");
    reflectivedolpihne->SetMeshGroup(GRAPHICS->GetMeshGroup("dolphin"));
    reflectivedolpihne->SetShader("phong_shading_cube");
    reflectivedolpihne->material = GRAPHICS->GetMaterial("m_environment");
    reflectivedolpihne->SetColor(glm::vec3(0.6f));
    reflectivedolpihne->transform.Translate(glm::vec3(19, -6.5f, -15.7f));
    reflectivedolpihne->transform.Scale(glm::vec3(15.f));
    reflectivedolpihne->transform.Rotate(-84, glm::vec3(0.63f, 0.4f, 0.35f));
    reflectivedolpihne->drawmode = 1;
    reflectivedolpihne->isUsingCubeMapTexture = true;
    reflectivedolpihne->environmentmapping_mode = 0;
    reflectivedolpihne->isModePhongShading_EnvironmentMapping = true;
    reflectivedolpihne->mixRate =0.3f;



    jet1 = new Object("jet1");
    jet1->SetMeshGroup(GRAPHICS->GetMeshGroup("jet"));
    jet1->SetShader("phong_shading");
    jet1->material = GRAPHICS->GetMaterial("m_jet");
    jet1->transform.Translate(glm::vec3(185, 7.2f, -195.f));
    jet1->transform.Scale(glm::vec3(5.f));
    jet1->transform.Rotate(45, glm::vec3(0, 1, 0));
    jet1->drawmode = 1;

    jet2 = new Object("jet2",jet1);
    jet2->SetColor(glm::vec3(0.6f));
    jet2->transform.Translate(glm::vec3(180, 6.5f, -200.f));
    jet2->transform.Scale(glm::vec3(3.f));

    jet3 = new Object("jet3", jet2);
    jet3->SetColor(glm::vec3(0.6f));
    jet3->transform.Translate(glm::vec3(190, 6.5f, -190.f));


    centerobj = new Object("centerobject");
    centerobj->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
    centerobj->SetShader("phong_shading_cube");
    centerobj->material = GRAPHICS->GetMaterial("m_centerobj");
    centerobj->transform.Translate(glm::vec3(0, -3.f, 0.0f));
    centerobj->transform.Scale(glm::vec3(3.f));
    centerobj->drawmode = 1;
    centerobj->mapping_mode = 1;
    centerobj->isUsingCubeMapTexture = true;

    GRAPHICS->centerobj = centerobj;

    GRAPHICS->camera.View(glm::vec3(0.0f, 4.0f, 25));
    GRAPHICS->camera.SetPitch(-10);
    GRAPHICS->camera.SetYaw(-90);
    IMGUIMANAGER->Init();
}

void TestLevel::Update()
{
    if (IMGUIMANAGER->lightNumberChanged||IMGUIMANAGER->lightoption!=IMGUIMANAGER->prev_lightoption)
    {
        OBJECTMANAGER->DeleteAllLights();
        lights.clear();
        for (int i = 0; i < IMGUIMANAGER->lightNumber; i++)
        {
            LightObject* lightsource = new LightObject("light" + std::to_string(i));
            lightsource->SetMeshGroup(GRAPHICS->GetMeshGroup("sphere"));
            lightsource->SetShader("light");
            lightsource->transform.Scale(glm::vec3(0.2, 0.2, 0.2));
            lightsource->drawmode = 1;
            lightsource->type = LightType::POINT;
            lightsource->material = GRAPHICS->GetMaterial("m_light");

            lights.push_back(lightsource);
        }
        for (int i = 0; i < lights.size(); i++)
        {
            lights[i]->transform.Translate(glm::vec3(cos(time_count + (float)i * 6.28f / lights.size()) * 9, -3, sin(time_count + (float)i * 6.28f / lights.size()) * 9));
        }
        IMGUIMANAGER->lightNumberChanged = false;
        if(IMGUIMANAGER->lightoption==2)
        {
            int iter = 0;
            for (auto light : lights)
            {
                if (iter % 8 == 7)
                {
                    light->ambient = glm::vec3(1.f, 0.1f, 0.1f);
                    light->diffuse = glm::vec3(1.f, 0.1f, 0.1f);
                    light->specular = glm::vec3(1.f, 0.1f, 0.1f);
                }
                else if (iter % 8 == 6)
                {
                    light->ambient = glm::vec3(1.f, 0.5f, 0.1f);
                    light->diffuse = glm::vec3(1.f, 0.5f, 0.1f);
                    light->specular = glm::vec3(1.f, 0.5f, 0.1f);
                }
                else if (iter % 8 == 5)
                {
                    light->ambient = glm::vec3(0.5f, 0.5f, 0.1f);
                    light->diffuse = glm::vec3(0.5f, 0.5f, 0.1f);
                    light->specular = glm::vec3(0.5f, 0.5f, 0.1f);
                }
                else if (iter % 8 == 4)
                {
                    light->ambient = glm::vec3(0.1f, 1.f, 0.1f);
                    light->diffuse = glm::vec3(0.1f, 1.f, 0.1f);
                    light->specular = glm::vec3(0.1f, 1.f, 0.1f);
                }
                else if (iter % 8 == 3)
                {
                    light->ambient = glm::vec3(0.1f, 0.1f, 1.f);
                    light->diffuse = glm::vec3(0.1f, 0.1f, 1.f);
                    light->specular = glm::vec3(0.1f, 0.1f, 1.f);
                }
                else if (iter % 8 == 2)
                {
                    light->ambient = glm::vec3(0.1f, 0.1f, 0.6f);
                    light->diffuse = glm::vec3(0.1f, 0.1f, 0.6f);
                    light->specular = glm::vec3(0.1f, 0.1f, 0.6f);
                }
                else if (iter % 8 == 1)
                {
                    light->ambient = glm::vec3(0.6f, 0.1f, 1.f);
                    light->diffuse = glm::vec3(0.6f, 0.1f, 1.f);
                    light->specular = glm::vec3(0.6f, 0.1f, 1.f);
                }
                else
                {
                    light->ambient = glm::vec3(1.f, 1.f, 1.f);
                    light->diffuse = glm::vec3(1.f, 1.f, 1.f);
                    light->specular = glm::vec3(1.f, 1.f, 1.f);
                }

                light->type = static_cast<LightType>(iter % 2 == 0 ? 0 : 2);

                iter += 1;
            }
        }
    }
    if (IMGUIMANAGER->shouldRotatelight)
    {
        time_count += TIMEMANAGER->deltaTime;
        for (int i = 0; i < lights.size(); i++)
        {
            lights[i]->transform.Translate(glm::vec3(cos(time_count + (float)i * 6.28f / lights.size()) * 9, -3, sin(time_count + (float)i * 6.28f / lights.size()) * 9));
        }
    }
    if (obj != nullptr)
    {
        obj->transform.Rotate(TIMEMANAGER->deltaTime, glm::vec3(0, 1, 0));
    }
    if(jet1!=nullptr&&jet2!=nullptr&&jet3!=nullptr)
    {
        float move =30;
        jet1->transform.Move(glm::vec3(-move, 0, move));
        jet2->transform.Move(glm::vec3(-move, 0, move));
        jet3->transform.Move(glm::vec3(-move, 0, move));
        if(jet1->transform.position.x<-500)
        {
            jet1->transform.Translate(glm::vec3(185, 7.2f, -195.f));
            jet2->transform.Translate(glm::vec3(180, 6.5f, -200.f));
            jet3->transform.Translate(glm::vec3(190, 6.5f, -190.f));
        }

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
