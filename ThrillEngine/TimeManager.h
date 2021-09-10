#pragma once
#include "EngineCore.h"

class TimeManager : public EngineCore
{
public:
    void Init() override;
    void Update() override;
    ~TimeManager();

    float deltaTime, lastFrame, currentFrame;
};
extern TimeManager* TIMEMANAGER;