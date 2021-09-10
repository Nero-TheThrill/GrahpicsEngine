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

    GRAPHICS->LoadShader("../shaders/texture.vert", "texturevert", VERTEX);
    GRAPHICS->LoadShader("../shaders/texture.frag", "texturefrag", FRAGMENT);
    GRAPHICS->CompileShader("texturevert", "texturefrag", "texture");


    GRAPHICS->LoadTexture("../images/awesomeface.png", "face", RGBA);
    GRAPHICS->LoadTexture("../images/container.jpg", "container", RGB);
    GRAPHICS->LoadTexture("../images/lol.png", "lol", RGB);

    Material MTest, MTexture;
    MTest.PickShader("test");
    MTexture.PickShader("texture");

    MTest.set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    MTest.set("objectColor", glm::vec3(0.0f, 1.0f, 1.0f));

  //  MTexture.AddValue("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    MTexture.set("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

    GRAPHICS->AddMaterial("MTest", MTest);
    GRAPHICS->AddMaterial("MTexture", MTexture);

    LevelStructure* testlevel = new TestLevel();
    LEVELMANAGER->InsertLevel(testlevel, 1);
    LEVELMANAGER->ChangeLevel(1);
    LevelStructure* testlevel1 = new TestLevel1();
    LEVELMANAGER->InsertLevel(testlevel1, 2);



    ThrillEngine->Init();





    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

