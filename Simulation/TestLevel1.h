#pragma once
#include "LevelStructure.h"
#include "LightObject.h"
#include "Object.h"
class TestLevel1 : public LevelStructure
{
public:
    TestLevel1();
    void Init() override;
    void Update() override;
    void Close() override;
    ~TestLevel1();
private:
    Object* plane, * orbit, * centerobj, * obj, * ramus, * dragon, * bumblebee;
    std::vector<LightObject*> lights;
    Object* skysphere;
    float time_count;

};

