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
    Object* plane, * orbit, * centerobj, * obj, * ramus, * dragon,*bumblebee,*jet1,*jet2,*jet3;
    std::vector<LightObject*> lights;
    Object* skysphere;
    float time_count;
  
};

