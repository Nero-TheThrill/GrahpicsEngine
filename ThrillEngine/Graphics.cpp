#include "Graphics.h"
#include<array>
#include <sstream>
#include<fstream>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include  "glm/gtx/hash.hpp"
#include "Input.h"
#include "LineMesh.h"
#include "ModelMesh.h"
#include "SphereMesh.h"

Graphics* GRAPHICS = nullptr;


Graphics::Graphics()
{
    GRAPHICS = this;
}

void Graphics::Init()
{
    camera.Projection(45, 0.1f, 200.f); //should update every screen size changes.
    camera.View(glm::vec3(0.0f, 0.0f, 20)); //should update every camera moves
    InitPVmatrices();
    UpdatePVmatrices();
    LineMesh* linemesh = new LineMesh();
    linemesh->name = "linemesh";
    MeshGroup* m_linemesh = new MeshGroup;
    m_linemesh->name = "linemesh";
    m_linemesh->AddMesh(linemesh);
    m_linemesh->Init();
    meshgroups.insert(std::pair<std::string, MeshGroup*>("line", m_linemesh));
    std::cout << "Initialize Graphics" << std::endl;
}

void Graphics::Update()
{
    glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    UpdatePVmatrices();
    //camera.MouseMoveUpdate();
    camera.MouseScrollUpdate();
}

Graphics::~Graphics()
{
    for (auto m : materials)
    {
        delete m.second;
        m.second = nullptr;
    }
    for (auto m : meshgroups)
    {
        delete m.second;
        m.second = nullptr;
    }
    for (auto shader : shaders)
    {
        glDeleteProgram(shader.second.program_handle);
    }
    std::cout << "Graphics Destructor Called" << std::endl;
}

void Graphics::InitPVmatrices()
{

    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));



}

void Graphics::UpdatePVmatrices()
{
    glm::mat4 projection = camera.GetProjectionMatrix();
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
    if ((!vertexshader_result) || (!fragmentshader_result)) {
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
        Shader s;
        s.name = program_id;
        s.program_handle = program_handle;
        shaders.insert(std::pair<std::string, Shader>(program_id, s));
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

Shader Graphics::GetShader(const std::string& id)
{
    return shaders[id];
}

void Graphics::LoadShader(const std::string& path, const std::string& id, ShaderType type)
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
    switch (type)
    {
    case ShaderType::FRAGMENT:
        fragment_shaders.insert(std::pair<std::string, std::string>(id, buffer.str()));
        break;

    case ShaderType::VERTEX:
        vertex_shaders.insert(std::pair<std::string, std::string>(id, buffer.str()));
        break;

    default:
        std::cout << "wrong type" << std::endl;
        break;
    }

}

unsigned Graphics::GetTexture(const std::string& texture_id)
{
    if (textures.find(texture_id) == textures.end())
    {
        return 0;
    }
    else
    {
        return textures[texture_id];
    }
}

void Graphics::AddTexture(const std::string& texture_id, unsigned texture)
{
    textures.insert(std::pair<std::string, unsigned>(texture_id, texture));
}

void Graphics::LoadTexture(const std::string& path, const std::string& texture_id, ImageType image_type)
{
    if (textures.find(texture_id) == textures.end())
    {
        int width, height, nrChannels;
        unsigned char* data;
        unsigned texture;
        stbi_set_flip_vertically_on_load(true);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps


        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            if (image_type == ImageType::RGBA)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else if (image_type == ImageType::RGB)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << path << std::endl;
            return;
        }
        stbi_image_free(data);
        GRAPHICS->AddTexture(texture_id, texture);
    }
}


MeshGroup* Graphics::GetMeshGroup(const std::string& mesh_id)
{
    if (meshgroups.find(mesh_id) == meshgroups.end())
    {
        return nullptr;
    }
    else
    {
        return meshgroups[mesh_id];
    }
}

void Graphics::AddSphereMesh()
{
    MeshGroup* m_sphere = new MeshGroup();
    float PI = 22.f / 7.f;
    SphereMesh* sphere = new SphereMesh();
    float x, y, z, xy;
    float s, t;
    int sectorCount = 50;
    int stackCount = 50;
    float sectorStep = 2.f * PI / static_cast<float>(sectorCount);
    float stackStep = PI / static_cast<float>(stackCount);
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2.f - static_cast<float>(i) * stackStep;
        xy = cos(stackAngle);
        z = sin(stackAngle);


        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = static_cast<float>(j) * sectorStep;

            x = xy * cos(sectorAngle);
            y = xy * sin(sectorAngle);
            sphere->positions_use_indices.push_back(glm::vec3(x, y, z));
            sphere->vertex_normals.push_back(glm::vec3(x, y, z));
            s = static_cast<float>(j) / static_cast<float>(sectorCount);
            t = static_cast<float>(i) / static_cast<float>(stackCount);
            sphere->texcoords_use_indices.push_back(glm::vec2(1 - s, t));
        }
    }
    int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; j++, k1++, k2++)
        {
            if (i != 0)
            {
                sphere->indices.push_back(k1);
                sphere->indices.push_back(k2);
                sphere->indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
                sphere->indices.push_back(k1 + 1);
                sphere->indices.push_back(k2);
                sphere->indices.push_back(k2 + 1);
            }
        }


    }
    m_sphere->name = "customsphere";
    sphere->name = "customsphere";
    m_sphere->AddMesh(sphere);
    m_sphere->Init();
    meshgroups.insert(std::pair<std::string, MeshGroup*>("customsphere", m_sphere));
}

void Graphics::SetBackgroundColor(glm::vec4 bgcolor)
{
    background_color = bgcolor;
}

void Graphics::SetLightObject(Object* obj)
{
    light = obj;
}

void Graphics::AddMaterial(const std::string& material_id, Material* material)
{
    materials.insert(std::pair<std::string, Material*>(material_id, material));
}


Material* Graphics::GetMaterial(const std::string& material_id)
{
    if (materials.find(material_id) == materials.end())
    {
        return nullptr;
    }
    else
    {
        return materials[material_id];
    }
}

std::unordered_map<std::string, Material*> Graphics::GetAllMaterial()
{
    return materials;
}

std::unordered_map<std::string, MeshGroup*> Graphics::GetAllMeshGroups()
{
    return meshgroups;
}

std::unordered_map<std::string, Shader> Graphics::GetAllShaders()
{
    return shaders;
}

