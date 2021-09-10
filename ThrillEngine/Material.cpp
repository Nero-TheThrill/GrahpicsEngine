#include "Material.h"

#include "Graphics.h"


Material::Material()
{
    
}

Material::~Material()
{
    //need to delete all shader programs.
}

void Material::Use()
{
    glUseProgram(shader.program_handle);
}

void Material::UnUse()
{
    glUseProgram(0);
}

void Material::Update()
{
    for(auto v:set_values_v3)
    {
        shader.set(v.first, v.second);
    }
}

void Material::PickShader(const std::string& input_program)
{
    shader.program_handle = GRAPHICS->GetProgramHandle(input_program);
}

void Material::AddValue(const std::string& value_id, glm::vec3 input)
{
    set_values_v3.insert(std::pair<std::string, glm::vec3>(value_id, input));
}

void Material::AddValue(const std::string& value_id, glm::vec4 input)
{
    set_values_v4.insert(std::pair<std::string, glm::vec4>(value_id, input));
}

void Material::AddValue(const std::string& value_id, float input)
{
    set_values_float.insert(std::pair<std::string, float>(value_id, input));
}

void Material::AddValue(const std::string& value_id, bool input)
{
    set_values_bool.insert(std::pair<std::string, bool>(value_id, input));
}

void Material::AddValue(const std::string& value_id, int input)
{
    set_values_int.insert(std::pair<std::string, int>(value_id, input));
}

void Material::AddValue(const std::string& value_id, glm::mat4 input)
{
    set_values_m4.insert(std::pair<std::string, glm::mat4>(value_id, input));
}

void Material::ChangeValue(const std::string& value_id, glm::vec3 input)
{
    set_values_v3[value_id] = input;
}

void Material::ChangeValue(const std::string& value_id, glm::vec4 input)
{
    set_values_v4[value_id] = input;
}

void Material::ChangeValue(const std::string& value_id, float input)
{
    set_values_float[value_id] = input;
}

void Material::ChangeValue(const std::string& value_id, bool input)
{
    set_values_bool[value_id] = input;
}

void Material::ChangeValue(const std::string& value_id, int input)
{
    set_values_int[value_id] = input;
}

void Material::ChangeValue(const std::string& value_id, glm::mat4 input)
{
    set_values_m4[value_id] = input;
}


GLuint Material::GetProgramHandle()
{
    return shader.program_handle;
}


//should make a unordered_map and store "value_name" and "uniform location" so that reduce calling "glGetUniformLocation"
