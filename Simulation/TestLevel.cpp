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

    bumblebee = nullptr;

    dragon = nullptr;

    jet1 = nullptr;
    jet2 = nullptr;
    jet3 = nullptr;

}

void TestLevel::Init()
{
    IMGUIMANAGER->useIMGUI = true;
    GRAPHICS->SetBackgroundColor(glm::vec4(0.6,0.65,0.7,1.0));

    orbit = new Object("orbit");
    orbit->SetMeshGroup(GRAPHICS->GetMeshGroup("line"));
    orbit->SetShader("test");
    orbit->SetColor(glm::vec3(1, 1, 1));
    orbit->transform.Translate(glm::vec3(0, -3, 0));
    orbit->transform.Scale(glm::vec3(9, 9, 9));


    plane = new Object("plane");
    plane->SetMeshGroup(GRAPHICS->GetMeshGroup("quad"));
    plane->SetShader("phong_shading");
    plane->material = GRAPHICS->GetMaterial("m_plane");
    plane->transform.Translate(glm::vec3(0, -7, 0));
    plane->transform.Rotate(-90, glm::vec3(1, 0, 0));
    plane->transform.Scale(glm::vec3(20.f));
    plane->drawmode = 1;


   

    obj = new Object("obj");
    obj->SetMeshGroup(GRAPHICS->GetMeshGroup("cube"));
    obj->SetShader("phong_shading");
    obj->material= GRAPHICS->GetMaterial("m_obj");
    obj->mapping_mode = 3;
    obj->transform.Translate(glm::vec3(0, 4.f, 0.0f));
    obj->transform.Scale(glm::vec3(2.f));
    obj->drawmode = 1;

    ramus = new Object("ramus");
    ramus->SetMeshGroup(GRAPHICS->GetMeshGroup("ramus"));
    ramus->SetShader("phong_shading");
    //ramus->material = GRAPHICS->GetMaterial("m_ramus");
    ramus->transform.Translate(glm::vec3(-10.7, -2.6f, -10.f));
    ramus->transform.Scale(glm::vec3(5.f));
    ramus->transform.Rotate(45, glm::vec3(0, 1, 0));
    ramus->drawmode = 1;

    dragon = new Object("dragon");
    dragon->SetMeshGroup(GRAPHICS->GetMeshGroup("dragon"));
    dragon->SetShader("phong_shading");
   // dragon->material = GRAPHICS->GetMaterial("m_dragon");
   // dragon->SetColor(glm::vec3(0.6f));
    dragon->transform.Translate(glm::vec3(-38.7, -1.9f, -16.6f));
    dragon->transform.Scale(glm::vec3(40.f));
    dragon->transform.Rotate(-35, glm::vec3(0, 1, 0));
    dragon->drawmode = 1;

    bumblebee = new Object("bumblebee");
    bumblebee->SetMeshGroup(GRAPHICS->GetMeshGroup("bumblebee"));
    bumblebee->SetShader("phong_shading");
  //  bumblebee->material = GRAPHICS->GetMaterial("m_bumblebee");
    bumblebee->SetColor(glm::vec3(0.6f));
    bumblebee->transform.Translate(glm::vec3(10, -2.2f, -5.3f));
    bumblebee->transform.Scale(glm::vec3(5.f));
    bumblebee->transform.Rotate(-45, glm::vec3(0, 1, 0));
    bumblebee->drawmode = 1;



    jet1 = new Object("jet1");
    jet1->SetMeshGroup(GRAPHICS->GetMeshGroup("jet"));
    jet1->SetShader("phong_shading");
    jet1->material = GRAPHICS->GetMaterial("m_jet");
    jet1->transform.Translate(glm::vec3(85, 7.2f, -95.f));
    jet1->transform.Scale(glm::vec3(5.f));
    jet1->transform.Rotate(45, glm::vec3(0, 1, 0));
    jet1->drawmode = 1;

    jet2 = new Object("jet2",jet1);
    jet2->SetColor(glm::vec3(0.6f));
    jet2->transform.Translate(glm::vec3(-80, 6.5f, -90.f));
    jet2->transform.Scale(glm::vec3(3.f));

    jet3 = new Object("jet3", jet2);
    jet3->SetColor(glm::vec3(0.6f));
    jet3->transform.Translate(glm::vec3(90, 6.5f, -100.f));



    centerobj = new Object("centerobject");
    centerobj->SetMeshGroup(GRAPHICS->GetMeshGroup("bunny_high_poly"));
    centerobj->SetShader("phong_shading");
    centerobj->material = GRAPHICS->GetMaterial("m_centerobj");
    centerobj->transform.Translate(glm::vec3(0, -3.f, 0.0f));
    centerobj->transform.Scale(glm::vec3(3.f));
    centerobj->drawmode = 1;
    centerobj->mapping_mode = 1;
    GRAPHICS->centerobj = centerobj;



  

    skysphere = new Object("skysphere");
    skysphere->SetMeshGroup(GRAPHICS->GetMeshGroup("customsphere"));
    skysphere->SetShader("nolight");
    skysphere->material = GRAPHICS->GetMaterial("m_skysphere");
    skysphere->transform.Scale(glm::vec3(500.f));
    skysphere->drawmode = 1;

    IMGUIMANAGER->Init();
}

void TestLevel::Update()
{
    if (IMGUIMANAGER->lightNumberChanged||IMGUIMANAGER->lightoption!=IMGUIMANAGER->prev_lightoption)
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
        GRAPHICS->camera.Move(glm::vec3(0, 1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_E))
    {
        GRAPHICS->camera.Move(glm::vec3(0, -1, 0));
    }
    if (Input::IsPressed(GLFW_KEY_D))
    {
        GRAPHICS->camera.MoveSide(2);
    }
    if (Input::IsPressed(GLFW_KEY_A))
    {
        GRAPHICS->camera.MoveSide(-2);
    }
    if (Input::IsPressed(GLFW_KEY_W))
    {
        GRAPHICS->camera.MoveForward(2);
    }
    if (Input::IsPressed(GLFW_KEY_S))
    {
        GRAPHICS->camera.MoveForward(-2);
    }
    if (Input::IsPressed(GLFW_KEY_RIGHT))
    {
        GRAPHICS->camera.RotateYaxis(2 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsPressed(GLFW_KEY_LEFT))
    {
        GRAPHICS->camera.RotateYaxis(-2 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsPressed(GLFW_KEY_DOWN))
    {
        GRAPHICS->camera.RotateXaxis(2 * TIMEMANAGER->deltaTime * 10.f);
    }
    if (Input::IsPressed(GLFW_KEY_UP))
    {
        GRAPHICS->camera.RotateXaxis(-2 * TIMEMANAGER->deltaTime * 10.f);
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
