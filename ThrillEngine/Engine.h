#pragma once
#include <vector>

class EngineCore;
class Engine
{
public:
    Engine();
    ~Engine();

    void Init();

    void Loop();

    void Quit();

    void AddCore(EngineCore* input_core);

private:
    std::vector<EngineCore*> enginecore;
    bool isgamerunning;
};