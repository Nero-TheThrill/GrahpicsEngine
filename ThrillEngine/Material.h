#pragma once
#include <glad/glad.h>

#include <string>


// Material class will be used in objectmanager when drawing.
// In draw part,  Use(id) -> draw function from object class-> UnUse()
class Material
{
public:
    ~Material();

    void Use();
    void UnUse();
    void SetProgramHandle(const std::string& input_program);
    GLuint GetProgramHandle();
    void set_bool(const std::string& value_name, bool value) const;
    void set_int(const std::string& value_name, int value) const;
    void set_float(const std::string& value_name, float value) const;
private:
    GLuint program_handle=0;

};
