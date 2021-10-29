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
    GRAPHICS->LoadTexture("../images/brickwall.jpg", "brickwall");
    GRAPHICS->LoadTexture("../images/brickwall_normal.jpg", "brickwall_normal");


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
    objloader.loadObject("../models/teapot.obj", "teapot");
    objloader.loadObject("../models/baron.obj", "baron");

    GRAPHICS->AddSphereMesh();




    ThrillEngine->Init();

    Material * objmat, * ramusmat, * centermat, * lightmat, * dragonmat, * bumblebeemat, * skymat, * jetmat, *testmat;

    new Material("m_default");

    objmat = new Material("m_obj");
    ramusmat = new Material("m_ramus");
    centermat = new Material("m_centerobj");
    lightmat = new Material("m_light");
    skymat = new Material("m_skysphere");
    dragonmat = new Material("m_dragon");
    bumblebeemat = new Material("m_bumblebee");
    jetmat = new Material("m_jet");
    testmat = new Material("m_test");
    lightmat->emissive = glm::vec3(0.6f);
    lightmat->kd = 0.3f;
    objmat->texture.SetAmbientTexture("test");
    objmat->texture.SetDiffuseTexture("me");

    ramusmat->texture.SetTexture("ramus");
    ramusmat->ka = 0.03f;
    ramusmat->kd = 0.3f;
    ramusmat->ks = 0.2f;

    dragonmat->texture.SetAmbientTexture("dragon");
    dragonmat->texture.SetDiffuseTexture("dragon");

    bumblebeemat->texture.SetAmbientTexture("bumblebee");
    bumblebeemat->texture.SetDiffuseTexture("bumblebee");

    jetmat->texture.SetTexture("jet");

    centermat->texture.SetDiffuseTexture("roofdiff");
    centermat->texture.SetSpecularTexture("roofspec");

    skymat->texture.SetTexture("space");

    testmat->texture.SetTexture("test");
    testmat->texture.ambient_texture = -1;
    testmat->texture.diffuse_texture = -1;
    testmat->texture.specular_texture = -1;
    testmat->ka = 0.03f;
    testmat->kd = 0.3f;
    testmat->ks = 0.2f;

    LEVELMANAGER->InsertLevel(new TestLevel(), 1);
    LEVELMANAGER->ChangeLevel(1);
    LEVELMANAGER->InsertLevel(new TestLevel1(), 2);







    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

