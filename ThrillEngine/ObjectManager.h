#pragma once
#include "EngineCore.h"
#include "LightObject.h"
#include "unordered_map"
#include "Object.h"
class ObjectManager : public EngineCore
{
public:
    ObjectManager();
    void Init() override;
    void Update() override;
    ~ObjectManager();
    void RegisterObject(Object* obj);
    void RegisterLight(LightObject* light);
    void DeleteAll();
    std::unordered_map<unsigned, Object*> GetAllObjects();
    std::unordered_map<unsigned, LightObject*> GetAllLights();
private:
    unsigned int genObjectsNum = 0;
    std::unordered_map<unsigned, Object*> objects;
    std::vector<decltype(objects)::key_type> need_to_be_erased;
    std::unordered_map<unsigned, LightObject*> lightobjects;
    std::vector<decltype(lightobjects)::key_type> light_to_be_erased;
};
extern ObjectManager* OBJECTMANAGER;
