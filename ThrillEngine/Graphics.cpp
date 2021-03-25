#include "Graphics.h"
#include<array>
#include <sstream>
#include<fstream>
#include <iostream>

#include "Input.h"



Graphics* GRAPHICS = nullptr;


void Graphics::Init()
{
    GRAPHICS = this;

    //should make a function to do these stuffs in main.cpp
    LoadVertexShader("../shaders/basic.vert","basicvertex");
    LoadFragmentShader("../shaders/basic.frag","basicfrag");
    CompileShader("basicvertex", "basicfrag", "box");

    LoadVertexShader("../shaders/basic1.vert", "basicvertex1");
    LoadFragmentShader("../shaders/basic1.frag", "basicfrag1");
    CompileShader("basicvertex1", "basicfrag1", "box1");

    LoadVertexShader("../shaders/texture.vert", "texturevert");
    LoadFragmentShader("../shaders/texture.frag", "texturefrag");
    CompileShader("texturevert", "texturefrag", "texture");


    camera.Projection(45.0f, 0.1f, 100.f); //should update every screen size changes.
    camera.View(glm::vec3(0.0f, 0.0f, -3.f)); //should update every camera moves
    InitVPmatrices();
    UpdateVPmatrices();
}

void Graphics::Update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Graphics::~Graphics()
{
}

void Graphics::InitVPmatrices()
{
    
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
  

}

void Graphics::UpdateVPmatrices()
{
    glm::mat4 projection =  camera.GetProjectionMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glm::mat4 view = camera.GetViewMatrix();
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboMatrices);
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
    GLint vertexshader_result, fragmentshader_result;
    glCompileShader(vertexshader_handle);
    glGetShaderiv(vertexshader_handle, GL_COMPILE_STATUS, &vertexshader_result);
    glCompileShader(fragmentshader_handle);
    glGetShaderiv(fragmentshader_handle, GL_COMPILE_STATUS, &fragmentshader_result);
    if ((!vertexshader_handle) || (!fragmentshader_handle)) {
        log_string = "shader compilation failed\n";
        GLint log_len;
        glGetShaderiv(vertexshader_handle, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            GLchar* log = new GLchar[log_len];
            GLsizei written_log_len;
            glGetShaderInfoLog(vertexshader_handle, log_len, &written_log_len, log);
            log_string += log;
            std::cout << log_string << std::endl;
            delete[] log;
        }
        glGetShaderiv(fragmentshader_handle, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            GLchar* log = new GLchar[log_len];
            GLsizei written_log_len;
            glGetShaderInfoLog(fragmentshader_handle, log_len, &written_log_len, log);
            log_string += log;
            std::cout << log_string << std::endl;
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
                std::cout << log_string << std::endl;
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
        std::cout << log_string << std::endl;
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
        std::cout << log_string << std::endl;
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
