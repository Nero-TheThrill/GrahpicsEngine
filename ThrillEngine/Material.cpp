#include "Material.h"

#include "Graphics.h"


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

void Material::SetProgramHandle(const std::string& input_program)
{
    shader.program_handle = GRAPHICS->GetProgramHandle(input_program);
}

GLuint Material::GetProgramHandle()
{
    return shader.program_handle;
}

void Material::SetColor(glm::vec4 input)
{
    color = input;
    glUniform4fv(glGetUniformLocation(shader.program_handle, "ourColor"), 1, &color.x);
}

//should make a unordered_map and store "value_name" and "uniform location" so that reduce calling "glGetUniformLocation"
