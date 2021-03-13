#include "Graphics.h"
#include<array>
#include <sstream>
#include<fstream>
#include "Input.h"

Graphics* GRAPHICS = nullptr;


void Graphics::Init()
{
    GRAPHICS = this;
    LoadVertexShader("../shaders/basic.vert","basicvertex");
    LoadFragmentShader("../shaders/basic.frag","basicfrag");
    CompileShader("basicvertex", "basicfrag", "box");

    LoadVertexShader("../shaders/basic1.vert", "basicvertex1");
    LoadFragmentShader("../shaders/basic1.frag", "basicfrag1");
    CompileShader("basicvertex1", "basicfrag1", "box1");


}

void Graphics::Update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



}

Graphics::~Graphics()
{
}

void Graphics::CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id)
{
    GLuint program_handle = glCreateProgram();
    if (0 == program_handle) {
        log_string = "Cannot create program handle";
        return;
    }
    GLuint vertexshader_handle = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentshader_handle = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar const* vertexshader[] = { vertex_shaders.find(vertexshader_id)->second.c_str() };
    GLchar const* fragmentshader[] = { fragment_shaders.find(fragmentshader_id)->second.c_str() };
    glShaderSource(vertexshader_handle, 1, vertexshader, NULL);
    glShaderSource(fragmentshader_handle, 1, fragmentshader, NULL);
    glCompileShader(vertexshader_handle);
    glCompileShader(fragmentshader_handle);


    GLint vertexshader_result, fragmentshader_result;
    glGetShaderiv(vertexshader_handle, GL_COMPILE_STATUS, &vertexshader_result);
    glGetShaderiv(fragmentshader_handle, GL_COMPILE_STATUS, &fragmentshader_result);
    if ((GL_FALSE == vertexshader_handle) && (GL_FALSE == fragmentshader_handle)) {
        log_string = "shader compilation failed\n";
        GLint log_len;
        glGetShaderiv(vertexshader_handle, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            GLchar* log = new GLchar[log_len];
            GLsizei written_log_len;
            glGetShaderInfoLog(vertexshader_handle, log_len, &written_log_len, log);
            log_string += log;
            delete[] log;
        }
        glGetShaderiv(fragmentshader_handle, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            GLchar* log = new GLchar[log_len];
            GLsizei written_log_len;
            glGetShaderInfoLog(fragmentshader_handle, log_len, &written_log_len, log);
            log_string += log;
            delete[] log;
        }
    }
    else { // attach the shader to the program object
        glAttachShader(program_handle, vertexshader_handle);
        glAttachShader(program_handle, fragmentshader_handle);
        program_handles.insert(std::pair<std::string, GLuint>(program_id, program_handle));
        glLinkProgram(program_handle);

        // validate the program
        glValidateProgram(program_handle);
        GLint status;
        glGetProgramiv(program_handle, GL_VALIDATE_STATUS, &status);
        if (GL_FALSE == status) {
            log_string = "Failed to validate shader program for current OpenGL context\n";
            GLint log_len;
            glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &log_len);
            if (log_len > 0) {
                GLchar* log_str = new GLchar[log_len];
                GLsizei written_log_len;
                glGetProgramInfoLog(program_handle, log_len, &written_log_len, log_str);
                log_string += log_str;
                delete[] log_str;
            }
            return;
        }
    }
}
void Graphics::LoadVertexShader(const std::string& path, const std::string& id)
{
    std::ifstream shader_file(path, std::ifstream::in);
    if (!shader_file) {
        log_string = "Error opening file " + path;
        return;
    }
    std::stringstream buffer;
    buffer << shader_file.rdbuf();
    shader_file.close();
    vertex_shaders.insert(std::pair<std::string, std::string>(id, buffer.str()));
}

void Graphics::LoadFragmentShader(const std::string& path, const std::string& id)
{
    std::ifstream shader_file(path, std::ifstream::in);
    if (!shader_file) {
        log_string = "Error opening file " + path;
        return;
    }
    std::stringstream buffer;
    buffer << shader_file.rdbuf();
    shader_file.close();
    fragment_shaders.insert(std::pair<std::string, std::string>(id, buffer.str()));
}

GLuint Graphics::GetProgramHandle(const std::string& program_id)
{
    return program_handles.find(program_id)->second;
}
