#include "Shader.h"

#include <iostream>


#include "Graphics.h"


void Shader::set(const std::string& value_name, glm::vec4 color) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    if (loc >= 0)
        glUniform4fv(loc, 1, &color.x);
    else
        std::cout << "Uniform variable " << value_name << " doesn't exist" << std::endl;
}

void Shader::set(const std::string& value_name, bool value) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    if (loc >= 0)
        glUniform1i(loc, value);
    else
        std::cout << "Uniform variable " << value_name << " doesn't exist" << std::endl;
}

void Shader::set(const std::string& value_name, int value) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    if (loc >= 0)
        glUniform1i(loc, value);
    else
        std::cout << "Uniform variable " << value_name << " doesn't exist" << std::endl;
}

void Shader::set(const std::string& value_name, float value) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    if (loc >= 0)
        glUniform1i(loc, value);
    else
        std::cout << "Uniform variable " << value_name << " doesn't exist" << std::endl;
}

void Shader::set(const std::string& value_name, glm::mat4 matrix) const
{
    GLint loc = glGetUniformLocation(program_handle, value_name.c_str());
    if (loc >= 0)
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
    else
        std::cout << "Uniform variable " << value_name << " doesn't exist" << std::endl;
}

