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
#include "ObjectManager.h"

Graphics* GRAPHICS = nullptr;


Graphics::Graphics()
{
    GRAPHICS = this;
}

void Graphics::Init()
{
    camera.Projection(45, 0.1f, 200.f);
    camera.View(glm::vec3(0.0f, 0.0f, 20));
    InitPVmatrices();
    InitLightInfo();
    LineMesh* linemesh = new LineMesh();
    linemesh->name = "linemesh";
    MeshGroup* m_linemesh = new MeshGroup();
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
    UpdateLightInfo();


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
        glDeleteProgram(shader.second.first.program_handle);
    }
    std::cout << "Graphics Destructor Called" << std::endl;
}

void Graphics::InitPVmatrices()
{

    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void Graphics::UpdatePVmatrices()
{
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glm::mat4 projection = camera.GetProjectionMatrix();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glm::mat4 view = camera.GetViewMatrix();
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

void Graphics::InitLightInfo()
{
    GLsizeiptr size = 112 * 16 + 80;// 16 * (sizeof(unsigned) + 5 * sizeof(glm::vec3) + 3 * sizeof(float)) + sizeof(unsigned)+3 * sizeof(float) + 3 * sizeof(glm::vec3);
    glGenBuffers(1, &uboLight);
    glBindBuffer(GL_UNIFORM_BUFFER, uboLight);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 1, uboLight, 0, size);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Graphics::UpdateLightInfo()
{
    glBindBuffer(GL_UNIFORM_BUFFER, uboLight);
    std::unordered_map<unsigned, LightObject*>lights = OBJECTMANAGER->GetAllLights();
    auto lightnumber = static_cast<unsigned>(IMGUIMANAGER->lightNumber);
    GLsizeiptr lightstride = 112;// (sizeof(unsigned) + 5 * sizeof(glm::vec3) + 3 * sizeof(float));
    int iter = 0;
    

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(unsigned), &lightnumber);
    glBufferSubData(GL_UNIFORM_BUFFER, 4, sizeof(float), &(camera.near));
    glBufferSubData(GL_UNIFORM_BUFFER, 8, sizeof(float), &(camera.far));
    glBufferSubData(GL_UNIFORM_BUFFER, 16, sizeof(glm::vec3), glm::value_ptr(camera.cam_position));
    glBufferSubData(GL_UNIFORM_BUFFER, 32, sizeof(glm::vec3), glm::value_ptr(fog_color));
    glBufferSubData(GL_UNIFORM_BUFFER, 48, sizeof(glm::vec3), glm::value_ptr(global_ambient_color));
    glBufferSubData(GL_UNIFORM_BUFFER, 64, sizeof(glm::vec3), glm::value_ptr(attenuation));


    for (auto light : lights)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride, sizeof(unsigned), &(light.second->type));
        light.second->direction = centerobj->transform.position-light.second->transform.position;
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 16, sizeof(glm::vec3), glm::value_ptr(light.second->direction));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 32, sizeof(glm::vec3), glm::value_ptr(light.second->transform.position));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 48, sizeof(glm::vec3), glm::value_ptr(light.second->ambient));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 64, sizeof(glm::vec3), glm::value_ptr(light.second->diffuse));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 80, sizeof(glm::vec3), glm::value_ptr(light.second->specular));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 92, sizeof(float), &(light.second->inner_angle));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 96, sizeof(float), &(light.second->outer_angle));
        glBufferSubData(GL_UNIFORM_BUFFER, 80 + iter * lightstride + 100, sizeof(float), &(light.second->falloff));
        iter++;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Graphics::CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id, bool is_ReCompile)
{
    GLuint program_handle;
    if (!is_ReCompile)
    {
        program_handle = glCreateProgram();
        if (0 == program_handle) {
            log_string = "Cannot create program handle";
            return;
        }

    }
    else
    {
        program_handle = shaders[program_id].first.program_handle;

    }
    glAttachShader(program_handle, vertex_shaders[vertexshader_id].first);
    glAttachShader(program_handle, fragment_shaders[fragmentshader_id].first);
    Shader s;
    s.name = program_id;
    s.program_handle = program_handle;

    shaders.insert(std::pair<std::string, std::pair<Shader, std::pair<std::string, std::string>>>(program_id, std::make_pair(s, std::make_pair(vertexshader_id, fragmentshader_id))));

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

Shader Graphics::GetShader(const std::string& id)
{
    return shaders[id].first;
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


    std::string stringbuffer = buffer.str();
    if (type == ShaderType::FRAGMENT || type == ShaderType::RELOAD_FRAGMENT)
    {
        GLuint fragmentshader_handle;
        GLint  fragmentshader_result;

        GLchar const* fragmentshader[] = { stringbuffer.c_str() };
        if (type == ShaderType::FRAGMENT)
            fragmentshader_handle = glCreateShader(GL_FRAGMENT_SHADER);
        else
            fragmentshader_handle = fragment_shaders[id].first;
        glShaderSource(fragmentshader_handle, 1, fragmentshader, NULL);
        glCompileShader(fragmentshader_handle);
        glGetShaderiv(fragmentshader_handle, GL_COMPILE_STATUS, &fragmentshader_result);
        if (!fragmentshader_result)
        {
            log_string = id + " fragment shader compilation failed\n";
            GLint log_len;
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
        if (type == ShaderType::FRAGMENT)
            fragment_shaders.insert(std::pair<std::string, std::pair<GLuint, std::string>>(id, std::make_pair(fragmentshader_handle, path)));
        else
            fragment_shaders[id].first = fragmentshader_handle;
    }
    else if (type == ShaderType::VERTEX || type == ShaderType::RELOAD_VERTEX)
    {
        GLuint vertexshader_handle;
        GLint vertexshader_result;
        GLchar const* vertexshader[] = { stringbuffer.c_str() };

        if (type == ShaderType::VERTEX)
            vertexshader_handle = glCreateShader(GL_VERTEX_SHADER);
        else
            vertexshader_handle = vertex_shaders[id].first;

        glShaderSource(vertexshader_handle, 1, vertexshader, NULL);
        glCompileShader(vertexshader_handle);
        glGetShaderiv(vertexshader_handle, GL_COMPILE_STATUS, &vertexshader_result);
        if (!vertexshader_result)
        {
            log_string = id + " vertex shader compilation failed\n";
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
        }
        if (type == ShaderType::VERTEX)
            vertex_shaders.insert(std::pair<std::string, std::pair<GLuint, std::string>>(id, std::make_pair(vertexshader_handle, path)));
        else
            vertex_shaders[id].first = vertexshader_handle;

    }
}

void Graphics::ReLoadShader()
{
    for (auto vertex_shader : vertex_shaders)
    {
        LoadShader(vertex_shader.second.second, vertex_shader.first, ShaderType::RELOAD_VERTEX);
    }
    for (auto fragment_shader : fragment_shaders)
    {
        LoadShader(fragment_shader.second.second, fragment_shader.first, ShaderType::RELOAD_FRAGMENT);
    }
    for (auto shader : shaders)
    {
        CompileShader(shader.second.second.first, shader.second.second.second, shader.first, true);
    }
}

int Graphics::GetTexture(const std::string& texture_id)
{
    if (textures.find(texture_id) == textures.end())
    {
        return -1;
    }
    else
    {
        return textures[texture_id];
    }
}

void Graphics::AddTexture(const std::string& texture_id, int texture)
{
    textures.insert(std::pair<std::string, int>(texture_id, texture));
}

void Graphics::LoadTexture(const std::string& path, const std::string& texture_id)
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps


        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            if (nrChannels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else if (nrChannels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << path << std::endl;
            return;
        }
        stbi_image_free(data);
        GRAPHICS->AddTexture(texture_id, static_cast<int>(texture));
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
    float PI = acos(-1);
    ModelMesh* sphere = new ModelMesh();
    float x, y, z, xy;
    float s, t;
    int sectorCount = 50;
    int stackCount = 50;
    float sectorStep = 2.f * PI / static_cast<float>(sectorCount);
    float stackStep = PI / static_cast<float>(stackCount);
    float sectorAngle, stackAngle;
    sphere->maxYval = 1;
    sphere->minYval = -1;
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
            sphere->texcoords_use_indices.push_back(glm::vec2(1 - s, 1-t));

            float u_sc = glm::degrees(atan2(y, x));
            u_sc += 180;

            float v_s = 180 - glm::degrees(acos(z / (sqrt(x * x + y * y + z * z))));

            float v_c = (z + 1) / 2.f;
            glm::vec3 Vec=glm::vec3(x, y, z);
            glm::vec3 absVec = abs(glm::vec3(x, y, z));
            glm::vec2 planar_uv;
            if (absVec.x >= absVec.y && absVec.x >= absVec.z)
            {
                Vec.x < 0 ? planar_uv.x = Vec.z / absVec.x : planar_uv.x = -Vec.z / absVec.x;
                planar_uv.y = Vec.y / absVec.x;
            }
            if (absVec.y >= absVec.x && absVec.y >= absVec.z)
            {
                Vec.y < 0 ? planar_uv.x = Vec.x / absVec.y : planar_uv.x = -Vec.x / absVec.y;
                planar_uv.y = Vec.z / absVec.y;
            }
            if (absVec.z >= absVec.y && absVec.z >= absVec.x)
            {
                Vec.z < 0 ? planar_uv.x = -Vec.x / absVec.z : planar_uv.x = Vec.x / absVec.z;
                planar_uv.y = Vec.y / absVec.z;
            }

            sphere->spherical_texcoords_use_indices.push_back(glm::vec2(1 - u_sc / 360.f, v_s / 180.f));
            sphere->cylindrical_texcoords_use_indices.push_back(glm::vec2(1 - u_sc / 360.f, v_c));
            sphere->planar_texcoords_use_indices.push_back((planar_uv + glm::vec2(1)) * 0.5f);

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

std::unordered_map < std::string, std::pair<Shader, std::pair<std::string, std::string>>> Graphics::GetAllShaders()
{
    return shaders;
}

