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
}

void TestLevel::Init()
{
    defaultmat = new Material("m_default");
    objmat = new Material("m_obj");
    ramusmat = new Material("m_ramus");
    centermat = new Material("m_centerobj");
    lightmat = new Material("m_light");
    lightmat->emissive = glm::vec3(0.6f);
    lightmat->kd = 0.3f;

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
    plane->material = defaultmat;
    plane->transform.Translate(glm::vec3(0, -7, 0));
    plane->transform.Rotate(-90, glm::vec3(1, 0, 0));
    plane->transform.Scale(glm::vec3(20.f));
    plane->drawmode = 1;


    objmat->texture.SetAmbientTexture("test");
    objmat->texture.SetDiffuseTexture("me");

    ramusmat->texture.SetTexture("ramus");
    ramusmat->ka = 0.03f;
    ramusmat->kd = 0.3f;
    ramusmat->ks = 0.2f;
    centermat->texture.SetDiffuseTexture("roofdiff");
    centermat->texture.SetSpecularTexture("roofspec");

    obj = new Object("obj");
    obj->SetMeshGroup(GRAPHICS->GetMeshGroup("cube"));
    obj->SetShader("phong_shading");
    obj->material= objmat;
    obj->mapping_mode = 3;
    obj->transform.Translate(glm::vec3(0, 5.f, 0.0f));
    obj->transform.Scale(glm::vec3(3.f));
    obj->drawmode = 1;

    ramus = new Object("ramus");
    ramus->SetMeshGroup(GRAPHICS->GetMeshGroup("ramus"));
    ramus->SetShader("phong_shading");
    ramus->material = ramusmat;
    ramus->transform.Translate(glm::vec3(-10.7, -2.6f, -10.f));
    ramus->transform.Scale(glm::vec3(5.f));
    ramus->transform.Rotate(45, glm::vec3(0, 1, 0));
    ramus->drawmode = 1;

    centerobj = new Object("centerobject");
    centerobj->SetMeshGroup(GRAPHICS->GetMeshGroup("bunny_high_poly"));
    centerobj->SetShader("phong_shading");
    centerobj->material = centermat;
    centerobj->transform.Translate(glm::vec3(0, -3.f, 0.0f));
    centerobj->transform.Scale(glm::vec3(3.f));
    centerobj->drawmode = 1;
    centerobj->mapping_mode = 1;
    GRAPHICS->centerobj = centerobj;


    IMGUIMANAGER->Init();
}

void TestLevel::Update()
{
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
            lightsource->material = GRAPHICS->GetMaterial("m_light");
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
    if (obj != nullptr)
    {
        obj->transform.Rotate(TIMEMANAGER->deltaTime, glm::vec3(0, 1, 0));
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
        GRAPHICS->camera.RotateYaxis(2);
    }
    if (Input::IsPressed(GLFW_KEY_U))
    {
        GRAPHICS->camera.RotateYaxis(-2);
    }
    if (Input::IsPressed(GLFW_KEY_SEMICOLON))
    {
        GRAPHICS->camera.RotateXaxis(2);
    }
    if (Input::IsPressed(GLFW_KEY_P))
    {
        GRAPHICS->camera.RotateXaxis(-2);
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
