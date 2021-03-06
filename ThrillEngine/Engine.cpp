#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Input.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "TimeManager.h"

Engine::Engine()
{
    isgamerunning = true;

    AddCore(new Application());
    AddCore(new Graphics());
    AddCore(new ObjectManager());
    AddCore(new LevelManager());
    AddCore(new TimeManager());
}

Engine::~Engine()
{
}

void Engine::Init()
{

    for (auto* e_core : enginecore)
        e_core->Init();
    Input::Init();
    APPLICATION->AppSet(1380 , 800);
}

void Engine::Loop()
{
    while (APPLICATION->shouldClose()&&isgamerunning)
    {
        Input::Update();
        for (auto* e_core : enginecore)
            e_core->Update();
    }
}

void Engine::Quit()
{
    isgamerunning = false;
    for(auto* e_core : enginecore)
    {
        delete e_core;
        e_core = nullptr;
    }
}

void Engine::AddCore(EngineCore* input_core)
{
    enginecore.push_back(input_core);
}
