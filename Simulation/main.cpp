#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "LevelManager.h"
#include "TestLevel.h"

int main()
{
    
    auto* ThrillEngine = new Engine();
    ThrillEngine->Init();


    GRAPHICS->LoadShader("../shaders/basic.vert", "basicvertex", VERTEX);
    GRAPHICS->LoadShader("../shaders/basic.frag", "basicfrag", FRAGMENT);
    GRAPHICS->CompileShader("basicvertex", "basicfrag", "box");

    GRAPHICS->LoadShader("../shaders/basic1.vert", "basicvertex1", VERTEX);
    GRAPHICS->LoadShader("../shaders/basic1.frag", "basicfrag1", FRAGMENT);
    GRAPHICS->CompileShader("basicvertex1", "basicfrag1", "box1");

    GRAPHICS->LoadShader("../shaders/texture.vert", "texturevert", VERTEX);
    GRAPHICS->LoadShader("../shaders/texture.frag", "texturefrag", FRAGMENT);
    GRAPHICS->CompileShader("texturevert", "texturefrag", "texture");


    GRAPHICS->LoadTexture("../images/awesomeface.png", "face", RGBA);
    GRAPHICS->LoadTexture("../images/container.jpg", "container", RGB);


    LevelStructure* testlevel = new TestLevel();
    LEVELMANAGER->InsertLevel(testlevel,1);
    LEVELMANAGER->ChangeLevel(1);
    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

