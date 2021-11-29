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
    void GenerateEnvironmentTextures(int count);
    void ReGenerateEnvironmentTextures(unsigned objId);
    ~ObjectManager();
    void RegisterObject(Object* obj);
    void RegisterLight(LightObject* light);
    void DeleteAll();
    void DeleteAllLights();
    Object* GetObject(std::string id);
    std::unordered_map<unsigned, Object*> GetAllObjects();
    std::unordered_map<unsigned, LightObject*> GetAllLights();
    SkyBox* skybox;
private:
    unsigned int UBO = 0;
    unsigned int genObjectsNum = 0;
    std::unordered_map<unsigned, Object*> objects;
    std::vector<decltype(objects)::key_type> need_to_be_erased;
    std::unordered_map<unsigned, LightObject*> lightobjects;
    std::vector<decltype(lightobjects)::key_type> light_to_be_erased;
    

    GLuint FBO=0;
    GLuint cubemapTextures[6];
    GLuint cubemapTextures1[6];
    GLuint cubemapTextures_regenerate[6];
    glm::vec3 camDirection[6];
    GLuint DepthBuffer = 0;

    glm::vec3 centerobj_position;
    glm::mat4 projection, view;
    glm::vec3 direction;

};
extern ObjectManager* OBJECTMANAGER;
