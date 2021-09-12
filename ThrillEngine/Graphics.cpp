#include "Graphics.h"
#include<array>
#include <sstream>
#include<fstream>
#include <iostream>

#include "Input.h"



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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
    case FRAGMENT:
        fragment_shaders.insert(std::pair<std::string, std::string>(id, buffer.str()));
        break;

    case VERTEX:
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
            if (image_type == RGBA)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else if (image_type == RGB)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
            return;
        }
        stbi_image_free(data);
        GRAPHICS->AddTexture(texture_id, texture);
    }
}

void Graphics::loadObject(const std::string& path, const std::string& mesh_id)
{
    Mesh* mesh = new Mesh();
    std::stringstream ss;
    std::ifstream in_file(path);
    std::string line = "";

    glm::vec3 tmp_vec3;
    glm::vec2 tmp_vec2;
    GLint tmp_glInt = 0;
    GLfloat tmp_glFloat = 0;


    if (!in_file.is_open())
    {
        assert("load failed");
    }


    while (std::getline(in_file, line))
    {
        std::string prefix = "";
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
            for (int i = 0; i < 3; i++)
            {
                ss >> tmp_glFloat;
                mesh->positions.push_back(tmp_glFloat);
            }
        }
        else if (prefix == "vt") // texture
        {
            for (int i = 0; i < 2; i++)
            {
                ss >> tmp_glFloat;
                mesh->texcoords.push_back(tmp_glFloat);
            }
        }
        else if (prefix == "vn") // normal
        {
            for (int i = 0; i < 3; i++)
            {
                ss >> tmp_glFloat;
                mesh->normals.push_back(tmp_glFloat);
            }
        }
        else if (prefix == "f") // faces
        {
            for (int i = 0; i < 3; i++)
            {
                ss >> tmp_glInt;
                mesh->position_indices.push_back(tmp_glInt - 1);
            }
        }
        else
        {

        }
    }
    float min_val_x = mesh->positions[0];
    float max_val_x = min_val_x;
    float max_val_y = min_val_x, min_val_y = min_val_x;
    float max_val_z = min_val_x, min_val_z = min_val_x;
    int iterator = 0;
    for (auto p : mesh->positions)
    {
        if (iterator % 3 == 0)
        {
            min_val_x = std::min(p, min_val_x);
            max_val_x = std::max(p, max_val_x);
        }
        else if (iterator % 3 == 1)
        {
            min_val_y = std::min(p, min_val_y);
            max_val_y = std::max(p, max_val_y);
        }
        else
        {
            min_val_z = std::min(p, min_val_z);
            max_val_z = std::max(p, max_val_z);
        }


        iterator++;
    }
    float denominator = std::max(std::max(max_val_x - min_val_x, max_val_y - min_val_y), max_val_z - min_val_z) / 2.f;
    float gap_x = max_val_x - min_val_x;
    float gap_y = max_val_y - min_val_y;
    float gap_z = max_val_z - min_val_z;
    float subtract_x = gap_x / 2.f + min_val_x;
    float subtract_y = gap_y / 2.f + min_val_y;
    float subtract_z = gap_z / 2.f + min_val_z;
    iterator = 0;
    for (auto p : mesh->positions)
    {
        if (iterator % 3 == 0)
            mesh->positions[iterator] = (p - subtract_x) / denominator;
        else if (iterator % 3 == 1)
            mesh->positions[iterator] = (p - subtract_y) / denominator;
        else
            mesh->positions[iterator] = (p - subtract_z) / denominator;

        iterator++;
    }
    meshes.insert(std::pair<std::string, Mesh*>(mesh_id, mesh));
}

Mesh* Graphics::GetMesh(const std::string& mesh_id)
{
    if (meshes.find(mesh_id) == meshes.end())
    {
        assert(std::cout << "no mesh" << std::endl);
    }
    else
    {
        return meshes[mesh_id];
    }
}

void Graphics::AddMaterial(const std::string& material_id, Material* material)
{
    materials.insert(std::pair<std::string, Material*>(material_id, material));
}


Material* Graphics::GetMaterial(const std::string& material_id)
{
    if (materials.find(material_id) == materials.end())
    {
        assert(std::cout << "no material" << std::endl);
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

