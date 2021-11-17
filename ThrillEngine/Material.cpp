#include "Material.h"
#include <iostream>
#include "Graphics.h"


Material::Material(const std::string& id,bool IsUsingCubeMapTexture)
{
    GRAPHICS->AddMaterial(id,this);
    name = id;
    if(!IsUsingCubeMapTexture)
        texture = new Texture();
    else
        texture = new CubeMapTexture();
    //std::cout << "Material<" << name << "> Constructor Called" << std::endl;
}

Material::~Material()
{
    delete texture;
    //std::cout << "Material<"<<name<<"> Destructor Called" << std::endl;
}

void Material::Use()
{
   
}

void Material::UnUse()
{
    
}

void Material::Update(Shader shader)
{
    shader.set("k_a", ka);
    shader.set("k_d", kd);
    shader.set("k_s", ks);
    shader.set("emissive", emissive);
    shader.set("ns", ns);
    texture->Update(shader);

    for(auto v:set_values_v3)
    {
        shader.set(v.first, v.second);
    }
    for (auto v : set_values_v4)
    {
        shader.set(v.first, v.second);
    }
    for (auto v : set_values_m4)
    {
        shader.set(v.first, v.second);
    }
    for (auto v : set_values_float)
    {
        shader.set(v.first, v.second);
    }
    for (auto v : set_values_int)
    {
        shader.set(v.first, v.second);
    }
    for (auto v : set_values_bool)
    {
        shader.set(v.first, v.second);
    }
}


void Material::set(const std::string& value_id, glm::vec3 input)
{
    if(set_values_v3.find(value_id)==set_values_v3.end())
    {
        set_values_v3.insert(std::pair<std::string, glm::vec3>(value_id, input));
    }
    else
    {
        set_values_v3[value_id] = input;
    }
}
   

void Material::set(const std::string& value_id, glm::vec4 input)
{
    if (set_values_v4.find(value_id) == set_values_v4.end())
    {
        set_values_v4.insert(std::pair<std::string, glm::vec4>(value_id, input));
    }
    else
    {
        set_values_v4[value_id] = input;
    }
}

void Material::set(const std::string& value_id, float input)
{
    if (set_values_float.find(value_id) == set_values_float.end())
    {
        set_values_float.insert(std::pair<std::string, float>(value_id, input));
    }
    else
    {
        set_values_float[value_id] = input;
    }
}

void Material::set(const std::string& value_id, bool input)
{
    if (set_values_bool.find(value_id) == set_values_bool.end())
    {
        set_values_bool.insert(std::pair<std::string, bool>(value_id, input));
    }
    else
    {
        set_values_bool[value_id] = input;
    }
}

void Material::set(const std::string& value_id, int input)
{
    if (set_values_int.find(value_id) == set_values_int.end())
    {
        set_values_int.insert(std::pair<std::string, int>(value_id, input));
    }
    else
    {
        set_values_int[value_id] = input;
    }
}

void Material::set(const std::string& value_id, glm::mat4 input)
{
    if (set_values_m4.find(value_id) == set_values_m4.end())
    {
        set_values_m4.insert(std::pair<std::string, glm::mat4>(value_id, input));
    }
    else
    {
        set_values_m4[value_id] = input;
    }
}




//should make a unordered_map and store "value_name" and "uniform location" so that reduce calling "glGetUniformLocation"
