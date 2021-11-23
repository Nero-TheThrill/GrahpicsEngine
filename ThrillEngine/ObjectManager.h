#pragma once
#include "EngineCore.h"
#include "LightObject.h"
#include "unordered_map"
#include "Object.h"
#include "SkyBox.h"

class ObjectManager : public EngineCore
{
public:
    ObjectManager();
    void Init() override;
    void Update() override;
    void EnvironmentTextureCallback(int w, int h);
    void GenerateEnvironmentTextures();
    ~ObjectManager();
    void RegisterObject(Object* obj);
    void RegisterLight(LightObject* light);
    void DeleteAll();
    Object* GetObject(std::string id);
    std::unordered_map<unsigned, Object*> GetAllObjects();
    std::unordered_map<unsigned, LightObject*> GetAllLights();
private:
    unsigned int genObjectsNum = 0;
    std::unordered_map<unsigned, Object*> objects;
    std::vector<decltype(objects)::key_type> need_to_be_erased;
    std::unordered_map<unsigned, LightObject*> lightobjects;
    std::vector<decltype(lightobjects)::key_type> light_to_be_erased;
    
    SkyBox* skybox;
    GLuint FBO=0;
    GLuint texture_top, texture_bottom, texture_front, texture_back, texture_left, texture_right;
    GLuint DepthBuffer = 0;
    Material* m_environment =nullptr;
    glm::vec3 centerobj_position;
    glm::mat4 projection, view;
    glm::vec3 direction;

};
extern ObjectManager* OBJECTMANAGER;
