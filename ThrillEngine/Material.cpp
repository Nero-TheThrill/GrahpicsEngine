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

void Material::set_bool(const std::string& value_name, bool value) const
{
    glUniform1i(glGetUniformLocation(program_handle, value_name.c_str()), (int)value);
}

void Material::set_int(const std::string& value_name, int value) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    glUniform1i(loc, value);
}

void Material::set_float(const std::string& value_name, float value) const
{
    glUniform1f(glGetUniformLocation(program_handle, value_name.c_str()), value);
}
