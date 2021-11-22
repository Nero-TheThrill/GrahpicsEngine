#include "ObjectManager.h"
#include <iostream>

#include "Application.h"
#include "Graphics.h"

ObjectManager* OBJECTMANAGER = nullptr;

ObjectManager::ObjectManager()
{
    int width=static_cast<int>(APPLICATION->GetWindowSize().x), height = static_cast<int>(APPLICATION->GetWindowSize().y);
    OBJECTMANAGER = this;
    genObjectsNum = 0;
    std::cout << "Object Manager Constructor Called" << std::endl;
    //TODO: Initialize framebufferobject
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glGenTextures(1, &texture_top);
    glBindTexture(GL_TEXTURE_2D, texture_top);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenTextures(1, &texture_bottom);
    glBindTexture(GL_TEXTURE_2D, texture_bottom);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenTextures(1, &texture_front);
    glBindTexture(GL_TEXTURE_2D, texture_front);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenTextures(1, &texture_back);
    glBindTexture(GL_TEXTURE_2D, texture_back);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenTextures(1, &texture_left);
    glBindTexture(GL_TEXTURE_2D, texture_left);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenTextures(1, &texture_right);
    glBindTexture(GL_TEXTURE_2D, texture_right);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


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

}

void ObjectManager::Init()
{
    if (GRAPHICS->GetMaterial("m_skybox") == nullptr)
    {
        Material* m_skybox = new Material("m_skybox", true);
        reinterpret_cast<CubeMapTexture*>(m_skybox->texture)->SetFrontTexture("skybox_front");
        reinterpret_cast<CubeMapTexture*>(m_skybox->texture)->SetBackTexture("skybox_back");
        reinterpret_cast<CubeMapTexture*>(m_skybox->texture)->SetLeftTexture("skybox_left");
        reinterpret_cast<CubeMapTexture*>(m_skybox->texture)->SetRightTexture("skybox_right");
        reinterpret_cast<CubeMapTexture*>(m_skybox->texture)->SetTopTexture("skybox_top");
        reinterpret_cast<CubeMapTexture*>(m_skybox->texture)->SetBottomTexture("skybox_bottom");
    }
    if(m_environment == nullptr)
    {
        m_environment = new Material("m_environment",true);
    }
    skybox = new SkyBox("skybox");
    skybox->SetShader("nolight");
    skybox->SetMeshGroup(GRAPHICS->GetMeshGroup("cube"));
    skybox->material = GRAPHICS->GetMaterial("m_skybox");
}

void ObjectManager::Update()
{

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
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if (obj->second->isUsingCubeMapTexture)
        {
            if (obj->second->alive)
            {
                centerobj_position = obj->second->transform.position;
                GenerateEnvironmentTextures();
                obj->second->material = m_environment;
                obj->second->Update();
            }
            else
            {
                need_to_be_erased.push_back(obj->first);
            }
        }
    }


}

void ObjectManager::EnvironmentTextureCallback(int w, int h)
{
    glBindTexture(GL_TEXTURE_2D, texture_top);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture_bottom);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture_front);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture_back);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture_left);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture_right);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_INT, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void ObjectManager::GenerateEnvironmentTextures()
{
    int width = static_cast<int>(APPLICATION->GetWindowSize().x), height = static_cast<int>(APPLICATION->GetWindowSize().y);
    //TODO: Bind framebufferobject
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    //////////////////////////////////////////////////////////////////////////////////.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_front, 0);
    GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0,GL_DEPTH_ATTACHMENT };
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is incomplete" << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    direction.x = cos(glm::radians(90.f)) * cos(glm::radians(0.f));
    direction.y = sin(glm::radians(0.f));
    direction.z = sin(glm::radians(90.f)) * cos(glm::radians(0.f));
    view = glm::lookAt(centerobj_position, centerobj_position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    //TODO: generate environment textures
    if (skybox != nullptr)
    {
        glDepthMask(GL_FALSE);
        skybox->Update();
        glDepthMask(GL_TRUE);
    }
    glEnable(GL_DEPTH_TEST);
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
    //////////////////////////////////////////////////////////////////////////////////
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_back, 0);
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is incomplete" << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    direction.x = cos(glm::radians(90.f)) * cos(glm::radians(180.f));
    direction.y = sin(glm::radians(180.f));
    direction.z = sin(glm::radians(90.f)) * cos(glm::radians(180.f));
    view = glm::lookAt(centerobj_position, centerobj_position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //TODO: generate environment textures
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
    //////////////////////////////////////////////////////////////////////////////////.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_top, 0);
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is incomplete" << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    direction.x = cos(glm::radians(90.f)) * cos(glm::radians(89.9f));
    direction.y = sin(glm::radians(89.9f));
    direction.z = sin(glm::radians(90.f)) * cos(glm::radians(89.9f));
    view = glm::lookAt(centerobj_position, centerobj_position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //TODO: generate environment textures
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
    //////////////////////////////////////////////////////////////////////////////////.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_bottom, 0);
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is incomplete" << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    direction.x = cos(glm::radians(270.f)) * cos(glm::radians(-89.9f));
    direction.y = sin(glm::radians(-89.9f));
    direction.z = sin(glm::radians(270.f)) * cos(glm::radians(-89.9f));
    view = glm::lookAt(centerobj_position, centerobj_position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //TODO: generate environment textures
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
    //////////////////////////////////////////////////////////////////////////////////.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_left, 0);
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is incomplete" << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    direction.x = cos(glm::radians(180.f)) * cos(glm::radians(0.f));
    direction.y = sin(glm::radians(0.f));
    direction.z = sin(glm::radians(180.f)) * cos(glm::radians(0.f));
    view = glm::lookAt(centerobj_position, centerobj_position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //TODO: generate environment textures
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
    //////////////////////////////////////////////////////////////////////////////////
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_right, 0);
    glDrawBuffers(2, drawBuffers);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO is incomplete" << std::endl;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, GRAPHICS->uboMatrices);
    projection = glm::perspective(glm::radians(90.f), 1.f, GRAPHICS->camera.near, GRAPHICS->camera.far);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    direction.x = cos(glm::radians(180.f)) * cos(glm::radians(180.f));
    direction.y = sin(glm::radians(180.f));
    direction.z = sin(glm::radians(180.f)) * cos(glm::radians(180.f));
    view = glm::lookAt(centerobj_position, centerobj_position + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    //TODO: generate environment textures
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
    //TODO: UnBind framebufferobject
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK_LEFT);



    //TODO: apply to the center object
    reinterpret_cast<CubeMapTexture*>(m_environment->texture)->SetTopTexture(texture_top);
    reinterpret_cast<CubeMapTexture*>(m_environment->texture)->SetBottomTexture(texture_bottom);
    reinterpret_cast<CubeMapTexture*>(m_environment->texture)->SetLeftTexture(texture_left);
    reinterpret_cast<CubeMapTexture*>(m_environment->texture)->SetRightTexture(texture_right);
    reinterpret_cast<CubeMapTexture*>(m_environment->texture)->SetFrontTexture(texture_front);
    reinterpret_cast<CubeMapTexture*>(m_environment->texture)->SetBackTexture(texture_back);

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

