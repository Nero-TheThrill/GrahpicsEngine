#pragma once
#include "EngineCore.h"
#include "unordered_map"
#include "Object.h"
class ObjectManager : public EngineCore
{
public:
    void Init() override;
    void Update() override;
    ~ObjectManager();
    void RegisterObject(Object* obj);
private:
    unsigned int genObjectsNum=0;
    std::unordered_map<unsigned, Object*> objects;
    std::vector<decltype(objects)::key_type> need_to_be_erased;
};
extern ObjectManager* OBJECTMANAGER;
