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

    GRAPHICS->LoadShader("../shaders/texture.vert", "texturevert", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/texture.frag", "texturefrag", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("texturevert", "texturefrag", "texture");

    GRAPHICS->LoadShader("../shaders/light.vert", "lightvert", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/light.frag", "lightfrag", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("lightvert", "lightfrag", "light");

    GRAPHICS->LoadTexture("../images/starwars.jpg", "starwars");
    GRAPHICS->LoadTexture("../images/earth.bmp", "earth");
    GRAPHICS->LoadTexture("../images/moon.bmp", "moon");
    GRAPHICS->LoadTexture("../images/camo.jpg", "camo");
    GRAPHICS->LoadTexture("../images/graycamo.png", "graycamo");
    GRAPHICS->LoadTexture("../images/space.png", "space");
    GRAPHICS->LoadTexture("../images/ramus.png", "ramus");
    GRAPHICS->LoadTexture("../images/baron.png", "baron");
    GRAPHICS->LoadTexture("../images/penguin.png", "penguin");

    objloader.loadObject("../models/human.obj", "human");
    objloader.loadObject("../models/ramus.obj", "ramus");
    objloader.loadObject("../models/rhino.obj", "rhino");
    objloader.loadObject("../models/starwars1.obj", "starwars");
    objloader.loadObject("../models/sphere.obj", "sphere");
    objloader.loadObject("../models/cube2.obj", "cube2");
    objloader.loadObject("../models/cube.obj", "cube");
    objloader.loadObject("../models/bunny.obj", "bunny");
    objloader.loadObject("../models/bunny_high_poly.obj", "bunny_high_poly");
    objloader.loadObject("../models/4Sphere.obj", "4Sphere");
    objloader.loadObject("../models/sphere_modified.obj", "sphere_modified");
    objloader.loadObject("../models/lucy_princeton.obj", "lucy_princeton");
    objloader.loadObject("../models/cup.obj", "cup");
    objloader.loadObject("../models/quad.obj", "quad");
    objloader.loadObject("../models/triangle.obj", "triangle");
    objloader.loadObject("../models/baron.obj", "baron");
    objloader.loadObject("../models/penguin.obj", "penguin");

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

