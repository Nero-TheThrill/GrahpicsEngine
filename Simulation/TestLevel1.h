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
    Object* plane, * centerobj, * obj, * dragon;
    std::vector<LightObject*> lights;
    float time_count;

};

