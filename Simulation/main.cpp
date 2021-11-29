#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "LevelManager.h"
#include "ObjectLoader.h"
#include "ObjectManager.h"
#include "TestLevel.h"
#include "TestLevel1.h"

int main()
{

    auto* ThrillEngine = new Engine();
    ObjectLoader objloader;


    GRAPHICS->LoadShader("../shaders/test.vert", "testvert", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/test.frag", "testfrag", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("testvert", "testfrag", "test");

    GRAPHICS->LoadShader("../shaders/phong_shading.vert", "v_phong_shading", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/phong_shading.frag", "f_phong_shading", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("v_phong_shading", "f_phong_shading", "phong_shading");


    GRAPHICS->LoadShader("../shaders/phong_lighting.vert", "v_phong_lighting", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/phong_lighting.frag", "f_phong_lighting", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("v_phong_lighting", "f_phong_lighting", "phong_lighting");

    GRAPHICS->LoadShader("../shaders/blinn_shading.vert", "v_blinn_shading", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/blinn_shading.frag", "f_blinn_shading", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("v_blinn_shading", "f_blinn_shading", "blinn_shading");


    GRAPHICS->LoadShader("../shaders/light.vert", "v_light", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/light.frag", "f_light", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("v_light", "f_light", "light");

    GRAPHICS->LoadShader("../shaders/nolight.vert", "v_nolight", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/nolight.frag", "f_nolight", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("v_nolight", "f_nolight", "nolight");


    GRAPHICS->LoadShader("../shaders/phong_shading_cube.vert", "v_phong_shading_cube", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/phong_shading_cube.frag", "f_phong_shading_cube", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("v_phong_shading_cube", "f_phong_shading_cube", "phong_shading_cube");




    GRAPHICS->LoadTexture("../images/graycamo.png", "jet");
    GRAPHICS->LoadTexture("../images/me.jpg", "me");
    GRAPHICS->LoadTexture("../images/space.png", "space");
    GRAPHICS->LoadTexture("../images/ramus.png", "ramus");
    GRAPHICS->LoadTexture("../images/test.png", "test");
    GRAPHICS->LoadTexture("../images/dragon.jpg", "dragon");
    GRAPHICS->LoadTexture("../images/bumblebee.jpg", "bumblebee");
    GRAPHICS->LoadTexture("../images/dolphin.jpg", "dolphin");

    GRAPHICS->LoadTexture("../images/skybox/TropicalSunnyDay_pz.jpg", "skybox_front");
    GRAPHICS->LoadTexture("../images/skybox/TropicalSunnyDay_nz.jpg", "skybox_back");
    GRAPHICS->LoadTexture("../images/skybox/TropicalSunnyDay_px.jpg", "skybox_right");
    GRAPHICS->LoadTexture("../images/skybox/TropicalSunnyDay_nx.jpg", "skybox_left");
    GRAPHICS->LoadTexture("../images/skybox/TropicalSunnyDay_py.jpg", "skybox_top");
    GRAPHICS->LoadTexture("../images/skybox/TropicalSunnyDay_ny.jpg", "skybox_bottom");


    objloader.loadObject("../models/LPTerrain.obj", "grass");
    objloader.loadObject("../models/dolphin.obj", "dolphin");
    objloader.loadObject("../models/jet.obj", "jet");
    objloader.loadObject("../models/bumblebee.obj", "bumblebee");
    objloader.loadObject("../models/dragon.obj", "dragon");
    objloader.loadObject("../models/cube.obj", "skycube");
    objloader.loadObject("../models/ramus.obj", "ramus");
    objloader.loadObject("../models/sphere.obj", "sphere");
    objloader.loadObject("../models/cube2.obj", "cube2");
    objloader.loadObject("../models/bunny.obj", "bunny");
    objloader.loadObject("../models/bunny_high_poly.obj", "bunny_high_poly");
    objloader.loadObject("../models/4Sphere.obj", "4Sphere");
    objloader.loadObject("../models/lucy_princeton.obj", "lucy_princeton");
    objloader.loadObject("../models/baron.obj", "baron");
    objloader.loadObject("../models/quad.obj", "quad");
    GRAPHICS->AddSphereMesh();




    ThrillEngine->Init();

    Material * centermat, * lightmat, * jetmat, *environmentmat, *skyboxmat,*groundmat;

    new Material("m_default");

    centermat = new Material("m_centerobj",true);
    reinterpret_cast<CubeMapTexture*>(centermat->texture)->SetEmissiveTexture("test");
    centermat->ka = glm::vec3(0.0f);
    centermat->kd = glm::vec3(0.6f);

    jetmat = new Material("m_jet");
    jetmat->texture->SetTexture("jet");

    lightmat = new Material("m_light");
    lightmat->emissive = glm::vec3(0.6f);
    lightmat->kd = glm::vec3(0.3f);

    environmentmat = new Material("m_environment", true);
    reinterpret_cast<CubeMapTexture*>(environmentmat->texture)->SetEmissiveTexture("dolphin");
    environmentmat->ka = glm::vec3(0.0f);
    environmentmat->kd = glm::vec3(0.3f);


    skyboxmat = new Material("m_skybox", true);
    reinterpret_cast<CubeMapTexture*>(skyboxmat->texture)->SetFrontTexture("skybox_front");
    reinterpret_cast<CubeMapTexture*>(skyboxmat->texture)->SetBackTexture("skybox_back");
    reinterpret_cast<CubeMapTexture*>(skyboxmat->texture)->SetLeftTexture("skybox_left");
    reinterpret_cast<CubeMapTexture*>(skyboxmat->texture)->SetRightTexture("skybox_right");
    reinterpret_cast<CubeMapTexture*>(skyboxmat->texture)->SetTopTexture("skybox_top");
    reinterpret_cast<CubeMapTexture*>(skyboxmat->texture)->SetBottomTexture("skybox_bottom");
    OBJECTMANAGER->skybox->material = skyboxmat;


    groundmat = new Material("m_ground");
    groundmat->emissive = glm::vec3(0.06f,0.07f,0.02f);
    groundmat->kd = glm::vec3(0.1f);
    groundmat->ka = glm::vec3(0.0f);
    groundmat->ks = glm::vec3(0.0f);



    LEVELMANAGER->InsertLevel(new TestLevel(), 1);
    LEVELMANAGER->ChangeLevel(1);
    LEVELMANAGER->InsertLevel(new TestLevel1(), 2);





    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

