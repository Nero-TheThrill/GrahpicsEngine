#pragma once
#include "LevelStructure.h"
#include "LightObject.h"
#include "Object.h"
class TestLevel : public LevelStructure
{
public:
    TestLevel();
    void Init() override;
    void Update() override;
    void Close() override;
    ~TestLevel();
private:
    Object* plane,*orbit ,* centerobj,*obj,*ramus;
    std::vector<LightObject*> lights;
    Object* skysphere;
    float time_count;
};

