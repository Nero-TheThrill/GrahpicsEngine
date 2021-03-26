#include "Material.h"

#include "Graphics.h"


Material::~Material()
{
    //need to delete all shader programs.
}

void Material::Use()
{
    glUseProgram(program_handle);
}

void Material::UnUse()
{
    glUseProgram(0);
}

void Material::SetProgramHandle(const std::string& input_program)
{
    program_handle = GRAPHICS->GetProgramHandle(input_program);
}

GLuint Material::GetProgramHandle()
{
    return program_handle;
}

void Material::set(const std::string& value_name, glm::vec4 color) const
{
    glUniform4fv(glGetUniformLocation(program_handle, value_name.c_str()),1, &color.x);
}

void Material::set(const std::string& value_name, bool value) const
{
    glUniform1i(glGetUniformLocation(program_handle, value_name.c_str()), value);
}

void Material::set(const std::string& value_name, int value) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    glUniform1i(loc, value);
}

void Material::set(const std::string& value_name, float value) const
{
    glUniform1f(glGetUniformLocation(program_handle, value_name.c_str()), value);
}

void Material::set(const std::string& value_name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(program_handle, value_name.c_str()),1,GL_FALSE, glm::value_ptr(matrix));
}

void Material::SetColor(glm::vec4 input)
{
    color = input;
    glUniform4fv(glGetUniformLocation(program_handle,"ourColor"), 1, &color.x);
}


//should make a unordered_map and store "value_name" and "uniform location" so that reduce calling "glGetUniformLocation"
