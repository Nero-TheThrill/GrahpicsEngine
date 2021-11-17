#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "LevelManager.h"
#include "ObjectLoader.h"
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





    GRAPHICS->LoadTexture("../images/graycamo.png", "jet");
    GRAPHICS->LoadTexture("../images/me.jpg", "me");
    GRAPHICS->LoadTexture("../images/space.png", "space");
    GRAPHICS->LoadTexture("../images/ramus.png", "ramus");
    GRAPHICS->LoadTexture("../images/test.png", "test");
    GRAPHICS->LoadTexture("../images/dragon.jpg", "dragon");
    GRAPHICS->LoadTexture("../images/bumblebee.jpg", "bumblebee");
    GRAPHICS->LoadTexture("../images/metal_roof_diff_512x512.png", "roofdiff");
    GRAPHICS->LoadTexture("../images/metal_roof_spec_512x512.png", "roofspec");

    GRAPHICS->LoadTexture("../images/skybox/Daylight Box_Front.bmp", "skybox_front");
    GRAPHICS->LoadTexture("../images/skybox/Daylight Box_Back.bmp", "skybox_back");
    GRAPHICS->LoadTexture("../images/skybox/Daylight Box_Right.bmp", "skybox_right");
    GRAPHICS->LoadTexture("../images/skybox/Daylight Box_Left.bmp", "skybox_left");
    GRAPHICS->LoadTexture("../images/skybox/Daylight Box_Top.bmp", "skybox_top");
    GRAPHICS->LoadTexture("../images/skybox/Daylight Box_Bottom.bmp", "skybox_bottom");

    objloader.loadObject("../models/starwars-millennium-falcon.obj", "stwas");
    objloader.loadObject("../models/girl.obj", "girl");
    objloader.loadObject("../models/jet.obj", "jet");
    objloader.loadObject("../models/bumblebee.obj", "bumblebee");
    objloader.loadObject("../models/dragon.obj", "dragon");
    objloader.loadObject("../models/cube.obj", "cube");
    objloader.loadObject("../models/ramus.obj", "ramus");
    objloader.loadObject("../models/rhino.obj", "rhino");
    objloader.loadObject("../models/starwars1.obj", "starwars");
    objloader.loadObject("../models/sphere.obj", "sphere");
    objloader.loadObject("../models/cube2.obj", "cube2");
    objloader.loadObject("../models/bunny.obj", "bunny");
    objloader.loadObject("../models/bunny_high_poly.obj", "bunny_high_poly");
    objloader.loadObject("../models/4Sphere.obj", "4Sphere");
    objloader.loadObject("../models/sphere_modified.obj", "sphere_modified");
    objloader.loadObject("../models/lucy_princeton.obj", "lucy_princeton");
    objloader.loadObject("../models/cup.obj", "cup");
    objloader.loadObject("../models/quad.obj", "quad");
    objloader.loadObject("../models/triangle.obj", "triangle");
    objloader.loadObject("../models/baron.obj", "baron");

    GRAPHICS->AddSphereMesh();




    ThrillEngine->Init();

    Material * objmat, * centermat, * lightmat, * skymat, * jetmat,*planemat;

    new Material("m_default");
    objmat = new Material("m_obj");
    centermat = new Material("m_centerobj");
    lightmat = new Material("m_light");
    skymat = new Material("m_skysphere");

    jetmat = new Material("m_jet");
    planemat = new Material("m_plane");

    lightmat->emissive = glm::vec3(0.6f);
    lightmat->kd = glm::vec3(0.3f);
    objmat->texture.SetAmbientTexture("test");
    objmat->texture.SetDiffuseTexture("me");



    jetmat->texture.SetTexture("jet");

    centermat->texture.SetDiffuseTexture("roofdiff");
    centermat->texture.SetSpecularTexture("roofspec");

    skymat->texture.SetTexture("space");

    planemat->ka = glm::vec3(0.08f);
    planemat->kd = glm::vec3(0.1f);
    planemat->ks = glm::vec3(0.1f);

    LEVELMANAGER->InsertLevel(new TestLevel(), 1);
    LEVELMANAGER->ChangeLevel(1);
    LEVELMANAGER->InsertLevel(new TestLevel1(), 2);







    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

