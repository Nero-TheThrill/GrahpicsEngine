#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "LevelManager.h"
#include "TestLevel.h"
#include "TestLevel1.h"

int main()
{

    auto* ThrillEngine = new Engine();



    GRAPHICS->LoadShader("../shaders/test.vert", "testvert", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/test.frag", "testfrag", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("testvert", "testfrag", "test");

    GRAPHICS->LoadShader("../shaders/texture.vert", "texturevert", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/texture.frag", "texturefrag", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("texturevert", "texturefrag", "texture");

    GRAPHICS->LoadShader("../shaders/light.vert", "lightvert", ShaderType::VERTEX);
    GRAPHICS->LoadShader("../shaders/light.frag", "lightfrag", ShaderType::FRAGMENT);
    GRAPHICS->CompileShader("lightvert", "lightfrag", "light");



    GRAPHICS->LoadTexture("../images/earth.bmp", "earth", ImageType::RGB);
    GRAPHICS->LoadTexture("../images/moon.bmp", "moon", ImageType::RGB);
    GRAPHICS->LoadTexture("../images/camo.jpg", "camo", ImageType::RGB);
    GRAPHICS->LoadTexture("../images/graycamo.png", "graycamo", ImageType::RGB);
    GRAPHICS->LoadTexture("../images/space.png", "space", ImageType::RGB);
    GRAPHICS->LoadTexture("../images/testmodel.jpg", "testmd", ImageType::RGB);
    GRAPHICS->LoadTexture("../images/ramus.png", "ramus", ImageType::RGBA);
    GRAPHICS->LoadTexture("../images/baron.png", "baron", ImageType::RGBA);
    GRAPHICS->LoadTexture("../images/penguin.png", "penguin", ImageType::RGBA);

    GRAPHICS->loadObject("../models/ramus.obj", "ramus");
    GRAPHICS->loadObject("../models/rhino.obj", "rhino");
   // GRAPHICS->loadObject("../models/starwars1.obj", "starwars");
    GRAPHICS->loadObject("../models/sphere.obj", "sphere");
    GRAPHICS->loadObject("../models/cube2.obj", "cube2");
    GRAPHICS->loadObject("../models/cube.obj", "cube");
    GRAPHICS->loadObject("../models/bunny.obj", "bunny");
    GRAPHICS->loadObject("../models/bunny_high_poly.obj", "bunny_high_poly");
    GRAPHICS->loadObject("../models/4Sphere.obj", "4Sphere");
    GRAPHICS->loadObject("../models/sphere_modified.obj", "sphere_modified");
    GRAPHICS->loadObject("../models/lucy_princeton.obj", "lucy_princeton");
    GRAPHICS->loadObject("../models/cup.obj", "cup");
    GRAPHICS->loadObject("../models/quad.obj", "quad");
    GRAPHICS->loadObject("../models/triangle.obj", "triangle");
    GRAPHICS->loadObject("../models/baron.obj", "baron");
    GRAPHICS->loadObject("../models/penguin.obj", "penguin");

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

