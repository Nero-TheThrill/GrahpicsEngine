#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "LevelManager.h"
#include "TestLevel.h"
#include "TestLevel1.h"

int main()
{

    auto* ThrillEngine = new Engine();



    GRAPHICS->LoadShader("../shaders/test.vert", "testvert", VERTEX);
    GRAPHICS->LoadShader("../shaders/test.frag", "testfrag", FRAGMENT);
    GRAPHICS->CompileShader("testvert", "testfrag", "test");

    //GRAPHICS->LoadShader("../shaders/texture.vert", "texturevert", VERTEX);
    //GRAPHICS->LoadShader("../shaders/texture.frag", "texturefrag", FRAGMENT);
    //GRAPHICS->CompileShader("texturevert", "texturefrag", "texture");

    GRAPHICS->LoadShader("../shaders/light.vert", "lightvert", VERTEX);
    GRAPHICS->LoadShader("../shaders/light.frag", "lightfrag", FRAGMENT);
    GRAPHICS->CompileShader("lightvert", "lightfrag", "light");



    GRAPHICS->LoadTexture("../images/awesomeface.png", "face", RGBA);
    GRAPHICS->LoadTexture("../images/container.jpg", "container", RGB);
    GRAPHICS->LoadTexture("../images/lol.png", "lol", RGB);



    Material* MTest = new Material("MTest"), * MLight = new Material("MLight");// , * MTexture = new Material("MTexture");
    MTest->PickShader("test");
    //MTexture->PickShader("texture");
    MLight->PickShader("light");

    MTest->set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    MLight->set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));


    GRAPHICS->loadObject("../models/cube.obj", "cube");
    GRAPHICS->loadObject("../models/sphere.obj", "sphere");
    GRAPHICS->loadObject("../models/bunny.obj", "bunny");
    GRAPHICS->loadObject("../models/4Sphere.obj", "4Sphere");
    GRAPHICS->loadObject("../models/sphere_modified.obj", "sphere_modified");
    GRAPHICS->loadObject("../models/lucy_princeton.obj", "lucy_princeton");
    GRAPHICS->loadObject("../models/bunny_high_poly.obj", "bunny_high_poly");
    GRAPHICS->loadObject("../models/quad.obj", "quad");
    GRAPHICS->loadObject("../models/cube2.obj", "cube2");
    LEVELMANAGER->InsertLevel(new TestLevel(), 1);
    LEVELMANAGER->ChangeLevel(1);
    LEVELMANAGER->InsertLevel(new TestLevel1(), 2);


    ThrillEngine->Init();





    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

