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



    GRAPHICS->LoadTexture("../images/me.jpg", "me");
    GRAPHICS->LoadTexture("../images/space.png", "space");
    GRAPHICS->LoadTexture("../images/ramus.png", "ramus");
    GRAPHICS->LoadTexture("../images/test.png", "test");
    GRAPHICS->LoadTexture("../images/metal_roof_diff_512x512.png", "roofdiff");
    GRAPHICS->LoadTexture("../images/metal_roof_spec_512x512.png", "roofspec");

    objloader.loadObject("../models/cube.obj", "cube");
    //objloader.loadObject("../models/human.obj", "human");
    objloader.loadObject("../models/ramus.obj", "ramus");
    //objloader.loadObject("../models/rhino.obj", "rhino");
    //objloader.loadObject("../models/starwars1.obj", "starwars");
    objloader.loadObject("../models/sphere.obj", "sphere");
    objloader.loadObject("../models/cube2.obj", "cube2");

    //objloader.loadObject("../models/bunny.obj", "bunny");
    objloader.loadObject("../models/bunny_high_poly.obj", "bunny_high_poly");
    objloader.loadObject("../models/4Sphere.obj", "4Sphere");
    //objloader.loadObject("../models/sphere_modified.obj", "sphere_modified");
    //objloader.loadObject("../models/lucy_princeton.obj", "lucy_princeton");
    //objloader.loadObject("../models/cup.obj", "cup");
    objloader.loadObject("../models/quad.obj", "quad");
    //objloader.loadObject("../models/triangle.obj", "triangle");
    objloader.loadObject("../models/baron.obj", "baron");
    //objloader.loadObject("../models/penguin.obj", "penguin");

    GRAPHICS->AddSphereMesh();


    ThrillEngine->Init();


    LEVELMANAGER->InsertLevel(new TestLevel(), 1);
    LEVELMANAGER->ChangeLevel(1);
    LEVELMANAGER->InsertLevel(new TestLevel1(), 2);







    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

