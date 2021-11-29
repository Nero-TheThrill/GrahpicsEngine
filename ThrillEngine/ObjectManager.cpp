#include "ObjectManager.h"
#include <iostream>

#include "Application.h"
#include "Graphics.h"

ObjectManager* OBJECTMANAGER = nullptr;
Object* objid1 = nullptr, * objid2 = nullptr;
ObjectManager::ObjectManager()
{
    int width=static_cast<int>(APPLICATION->GetWindowSize().x), height = static_cast<int>(APPLICATION->GetWindowSize().y);
    OBJECTMANAGER = this;
    genObjectsNum = 0;
    std::cout << "Object Manager Constructor Called" << std::endl;


    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    for (int i = 0; i < 6; i++)
    {
        glGenTextures(1, &cubemapTextures[i]);
        glBindTexture(GL_TEXTURE_2D, cubemapTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glGenTextures(1, &cubemapTextures1[i]);
        glBindTexture(GL_TEXTURE_2D, cubemapTextures1[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        glGenTextures(1, &cubemapTextures_regenerate[i]);
        glBindTexture(GL_TEXTURE_2D, cubemapTextures_regenerate[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glGenRenderbuffers(1, &DepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is complete" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    camDirection[0] = glm::vec3(0, 1, 0.000001f);
    camDirection[1] = glm::vec3(0, -1, -0.000001f);
    camDirection[2] = glm::vec3(-1, 0, 0);
    camDirection[3] = glm::vec3(1, 0, 0);
    camDirection[4] = glm::vec3(0, 0, 1);
    camDirection[5] = glm::vec3(0, 0, -1);
}

void ObjectManager::Init()
{

    skybox = new SkyBox("skybox");
    skybox->SetShader("nolight");
    skybox->SetMeshGroup(GRAPHICS->GetMeshGroup("skycube"));
    skybox->material = GRAPHICS->GetMaterial("m_skybox");
}

void ObjectManager::Update()
{
    glm::vec3 campos = GRAPHICS->camera.cam_position;
    if (skybox != nullptr)
    {
        glDepthMask(GL_FALSE);
        skybox->Update();
        glDepthMask(GL_TRUE);
    }
    for (std::unordered_map<unsigned, LightObject*>::iterator light = lightobjects.begin(); light != lightobjects.end(); light++)
    {
        if (!light->second->alive)
        {
            light_to_be_erased.push_back(light->first);
        }
    }
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if (!obj->second->isUsingCubeMapTexture)
        {
            if (obj->second->alive)
            {
                obj->second->Update();
            }
            else
            {
                need_to_be_erased.push_back(obj->first);
            }
        }
        else
        {

        }
    }

    int count = 0;
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if (obj->second->isUsingCubeMapTexture)
        {
            if (obj->second->alive)
            {
                centerobj_position = obj->second->transform.position;
                GenerateEnvironmentTextures(count);
                count++;
            }
            else
            {
                need_to_be_erased.push_back(obj->first);
            }
        }
    }
    GRAPHICS->camera.cam_position = campos;
    GRAPHICS->UpdateLightInfo();
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if (obj->second->isUsingCubeMapTexture)
        {
            if (obj->second->alive)
            {
                centerobj_position = obj->second->transform.position;

                ReGenerateEnvironmentTextures(obj->second->id);

                reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetTopTexture(cubemapTextures_regenerate[0]);
                reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetBottomTexture(cubemapTextures_regenerate[1]);
                reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetLeftTexture(cubemapTextures_regenerate[2]);
                reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetRightTexture(cubemapTextures_regenerate[3]);
                reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetFrontTexture(cubemapTextures_regenerate[4]);
                reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetBackTexture(cubemapTextures_regenerate[5]);
                obj->second->SendView(campos);
                obj->second->Update();
            }
            else
            {
                need_to_be_erased.push_back(obj->first);
            }
        }
    }

    for (auto light : light_to_be_erased)
    {
        lightobjects.erase(light);
    }
    for (auto obj : need_to_be_erased)
    {
        Object* deletethis = objects.find(obj)->second;
        objects.erase(obj);
        delete deletethis;
    }
    need_to_be_erased.clear();
    light_to_be_erased.clear();



}

void ObjectManager::EnvironmentTextureCallback(int w, int h)
{
    for (int i = 0; i < 6; i++)
    {
        glBindTexture(GL_TEXTURE_2D, cubemapTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, cubemapTextures1[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, cubemapTextures_regenerate[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    }

    glBindRenderbuffer(GL_RENDERBUFFER, DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void ObjectManager::GenerateEnvironmentTextures(int count)
{
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    int width = static_cast<int>(APPLICATION->GetWindowSize().x), height = static_cast<int>(APPLICATION->GetWindowSize().y);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT };
    for (int i = 0; i < 6; i++)
    {
        if(count==0)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cubemapTextures[i], 0);
        else if(count==1)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cubemapTextures1[i], 0);
        glDrawBuffers(2, drawBuffers);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "FBO is incomplete" << std::endl;
        }
        glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
        view = glm::lookAt(centerobj_position, centerobj_position + camDirection[i], glm::vec3(0.0f, 1.0f, 0.0f));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        if (skybox != nullptr)
        {
            glDepthMask(GL_FALSE);
            skybox->Update();
            glDepthMask(GL_TRUE);
        }
        for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
        {
            if (!obj->second->isUsingCubeMapTexture)
            {
                if (obj->second->alive)
                {
                    obj->second->Update();
                }
            }
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK_LEFT);
    
    GRAPHICS->UpdatePVmatrices();
}

void ObjectManager::ReGenerateEnvironmentTextures(unsigned objId)
{
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    int width = static_cast<int>(APPLICATION->GetWindowSize().x), height = static_cast<int>(APPLICATION->GetWindowSize().y);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT };
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    for (int i = 0; i < 6; i++)
    {
       
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cubemapTextures_regenerate[i], 0);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "FBO is incomplete" << std::endl;
        }
        glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
        view = glm::lookAt(centerobj_position, centerobj_position + camDirection[i], glm::vec3(0.0f, 1.0f, 0.0f));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        if (skybox != nullptr)
        {
            glDepthMask(GL_FALSE);
            skybox->Update();
            glDepthMask(GL_TRUE);
        }
        int count = 0;
        for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
        {
            if (obj->second->id != objId)
            {
                if (obj->second->isUsingCubeMapTexture)
                {
                    if (obj->second->alive)
                    {
                        if (count == 0)
                        {
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetTopTexture(cubemapTextures[0]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetBottomTexture(cubemapTextures[1]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetLeftTexture(cubemapTextures[2]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetRightTexture(cubemapTextures[3]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetFrontTexture(cubemapTextures[4]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetBackTexture(cubemapTextures[5]);
                        }
                        else if (count == 1)
                        {
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetTopTexture(cubemapTextures1[0]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetBottomTexture(cubemapTextures1[1]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetLeftTexture(cubemapTextures1[2]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetRightTexture(cubemapTextures1[3]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetFrontTexture(cubemapTextures1[4]);
                            reinterpret_cast<CubeMapTexture*>(obj->second->material->texture)->SetBackTexture(cubemapTextures1[5]);
                        }
                        count++;
                        obj->second->SendView(centerobj_position);
                        obj->second->Update();
                    }
                }
                else
                {
                    if (obj->second->alive)
                    {

                        obj->second->Update();
                    }
                }

              
            }
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK_LEFT);

    GRAPHICS->UpdatePVmatrices();
}

void ObjectManager::RegisterObject(Object* obj)
{
   
    genObjectsNum += 1;
    objects.insert(std::make_pair(genObjectsNum, obj));
    obj->id = genObjectsNum;
}

void ObjectManager::RegisterLight(LightObject* light)
{
    lightobjects.insert(std::make_pair(light->id, light));
}

void ObjectManager::DeleteAll()
{
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        need_to_be_erased.push_back(obj->first);
    }
    for (std::unordered_map<unsigned, LightObject*>::iterator light = lightobjects.begin(); light != lightobjects.end(); light++)
    {
        light_to_be_erased.push_back(light->first);
    }
    for (auto light : light_to_be_erased)
    {
        lightobjects.erase(light);
    }
    for (auto obj : need_to_be_erased)
    {
        Object* deletethis = objects.find(obj)->second;
        objects.erase(obj);
        delete deletethis;
    }
    objects.clear();
    lightobjects.clear();
    need_to_be_erased.clear();
    light_to_be_erased.clear();
}

void ObjectManager::DeleteAllLights()
{
    for (std::unordered_map<unsigned, LightObject*>::iterator light = lightobjects.begin(); light != lightobjects.end(); light++)
    {
        light_to_be_erased.push_back(light->first);
        need_to_be_erased.push_back(light->first);
    }
    for (auto light : light_to_be_erased)
    {
        lightobjects.erase(light);
    }
    for (auto obj : need_to_be_erased)
    {
        Object* deletethis = objects.find(obj)->second;
        objects.erase(obj);
        delete deletethis;
    }
    lightobjects.clear();
    light_to_be_erased.clear();
    need_to_be_erased.clear();
}

Object* ObjectManager::GetObject(std::string id)
{
    Object* result = nullptr;
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if(obj->second->name==id)
        {
            result = obj->second;
        }
    }
    return result;
}

std::unordered_map<unsigned, Object*> ObjectManager::GetAllObjects()
{
    return  objects;
}

std::unordered_map<unsigned, LightObject*> ObjectManager::GetAllLights()
{
    return lightobjects;
}


ObjectManager::~ObjectManager()
{
    for (auto obj : objects)
    {
        delete obj.second;
    }
    delete skybox;
    skybox = nullptr;
    std::cout << "ObjectManager Destructor Called" << std::endl;
}

