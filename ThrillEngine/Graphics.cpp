#include "Graphics.h"
#include<array>
#include <sstream>
#include<fstream>
#include <iostream>

#include "Input.h"
#include "ModelMesh.h"
#include "SphereMesh.h"


Graphics* GRAPHICS = nullptr;


Graphics::Graphics()
{
    GRAPHICS = this;
}

void Graphics::Init()
{
    camera.Projection(45, 0.1f, 100.f); //should update every screen size changes.
    camera.View(glm::vec3(0.0f, 0.0f, 20)); //should update every camera moves
    InitPVmatrices();
    UpdatePVmatrices();
}

void Graphics::Update()
{
    glClearColor(0.01f, 0.01f, 0.02f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    UpdatePVmatrices();
    //  camera.MouseMoveUpdate();
    camera.MouseScrollUpdate();
}

Graphics::~Graphics()
{
    for (auto m : materials)
    {
        delete m.second;
        m.second = nullptr;
    }
}

void Graphics::InitPVmatrices()
{

    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)


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

GLuint Graphics::GetProgramHandle(const std::string& program_id)
{
    return program_handles[program_id];
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
            std::cout << "Failed to load texture" << path <<std::endl;
            return;
        }
        stbi_image_free(data);
        GRAPHICS->AddTexture(texture_id, texture);
    }
}

void Graphics::loadObject(const std::string& path, const std::string& mesh_id)
{
    ModelMesh* mesh = new ModelMesh();
    std::stringstream ss;
    std::ifstream in_file(path);
    std::string line = "";

    int tmp_glInt = 0;
    float tmp_glFloat = 0;


    if (!in_file.is_open())
    {
        std::cout << "failed to load file : " << path << std::endl;
    }

    float min_val_x = FLT_MAX;
    float max_val_x = FLT_MIN;
    float max_val_y = max_val_x, min_val_y = min_val_x;
    float max_val_z = max_val_x, min_val_z = min_val_x;
    while (std::getline(in_file, line))
    {

        std::string prefix = "";
        glm::vec3 tmp_vec3;
        glm::vec2 tmp_vec2;
        ss.clear();
        ss.str(line);
        ss >> prefix;
        if (prefix == "#")
        {

        }
        else if (prefix == "o") // 
        {

        }
        else if (prefix == "s") // 
        {

        }
        else if (prefix == "use_mtl")
        {

        }
        else if (prefix == "v") // position
        {
            ss >> tmp_vec3.x >> tmp_vec3.y >> tmp_vec3.z;
            mesh->positions_use_indices.push_back(tmp_vec3);
            min_val_x = std::min(tmp_vec3.x, min_val_x);
            max_val_x = std::max(tmp_vec3.x, max_val_x);

            min_val_y = std::min(tmp_vec3.y, min_val_y);
            max_val_y = std::max(tmp_vec3.y, max_val_y);

            min_val_z = std::min(tmp_vec3.z, min_val_z);
            max_val_z = std::max(tmp_vec3.z, max_val_z);
        }
        else if (prefix == "vt") // texture
        {
            ss >> tmp_vec2.x >> tmp_vec2.y;
            mesh->texcoords.push_back(tmp_vec2);
        }
        else if (prefix == "vn") // normal
        {
            ss >> tmp_vec3.x >> tmp_vec3.y >> tmp_vec3.z;
            mesh->face_normals.push_back(tmp_vec3);
        }
        else if (prefix == "f") // faces
        {
            int stride = 0;
            while (ss >> tmp_glInt)
            {
                mesh->indices.push_back(tmp_glInt - 1);
                stride++;
            }
            mesh->face_stride = stride;

            //for (int i = 0; i < stride-2; i++)
            //{
            //    glm::vec3 v1 = glm::vec3(mesh->positions_use_indices[tmp_indices[0] * 3], mesh->positions_use_indices[tmp_indices[0] * 3 + 1], mesh->positions_use_indices[tmp_indices[0] * 3 + 2]),
            //        v2 = glm::vec3(mesh->positions_use_indices[tmp_indices[i + 1] * 3], mesh->positions_use_indices[tmp_indices[i + 1] * 3 + 1], mesh->positions_use_indices[tmp_indices[i + 1] * 3 + 2]),
            //        v3 = glm::vec3(mesh->positions_use_indices[tmp_indices[i + 2] * 3], mesh->positions_use_indices[tmp_indices[i + 2] * 3 + 1], mesh->positions_use_indices[tmp_indices[i + 2] * 3 + 2]);
            //    glm::vec3 cross_result = glm::cross(v2 - v1, v3 - v1);
            //    for (int i = 0; i < stride; i++)
            //    {
            //        mesh->normals.push_back(cross_result.x);
            //        mesh->normals.push_back(cross_result.y);
            //        mesh->normals.push_back(cross_result.z);
            //    }
            //}
        }
        else
        {

        }
    }
    float gap_x = max_val_x - min_val_x;
    float gap_y = max_val_y - min_val_y;
    float gap_z = max_val_z - min_val_z;
    float denominator = std::max(std::max(gap_x, gap_y), gap_z) / 2.f;

    float subtract_x = gap_x / 2.f + min_val_x;
    float subtract_y = gap_y / 2.f + min_val_y;
    float subtract_z = gap_z / 2.f + min_val_z;
    int iterator = 0;
    for (auto p : mesh->positions_use_indices)
    {
        mesh->positions_use_indices[iterator] = glm::vec3((p.x - subtract_x) / denominator, (p.y - subtract_y) / denominator, (p.z - subtract_z) / denominator);
        iterator++;
    }
    mesh->name = mesh_id;
    mesh->Init();
    meshes.insert(std::pair<std::string, Mesh*>(mesh_id, mesh));
}

Mesh* Graphics::GetMesh(const std::string& mesh_id)
{
    if (meshes.find(mesh_id) == meshes.end())
    {
        return nullptr;
    }
    else
    {
        return meshes[mesh_id];
    }
}

void Graphics::AddSphereMesh()
{
    float PI = 3.141596535f;
    SphereMesh* sphere = new SphereMesh();
    float x, y, z, xy;
    float s, t;
    int sectorCount = 100;
    int stackCount = 100;
    float sectorStep = 2.f * PI / static_cast<float>(sectorCount);
    float stackStep = PI / static_cast<float>(stackCount);
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2.f - static_cast<float>(i) * stackStep;
        xy = cosf(stackAngle);
        z = sinf(stackAngle);


        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = static_cast<float>(j) * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            sphere->positions_normals.push_back(glm::vec3(x,y,z));
            
            sphere->vertex_normals.push_back(glm::vec3(x, y, z));
            s = static_cast<float>(j) / static_cast<float>(sectorCount);
            t = static_cast<float>(i) / static_cast<float>(stackCount);
            sphere->texcoords.push_back(glm::vec2(s, t));
        }
    }
    int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
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

            //lineIndices.push_back(k1);
            //lineIndices.push_back(k2);
            //if (i != 0) 
            //{
            //    lineIndices.push_back(k1);
            //    lineIndices.push_back(k1 + 1);
            //}
        }


    }
    sphere->name = "customsphere";
    sphere->Init();
    meshes.insert(std::pair<std::string, Mesh*>("customsphere", sphere));
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

std::unordered_map<std::string, Mesh*> Graphics::GetAllMeshes()
{
    return meshes;
}

