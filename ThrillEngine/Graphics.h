#pragma once
#include <vector>
#include "EngineCore.h"
#include "Object.h"
#include <unordered_map>
#include "stb_image.h"
#include "Camera.h"

enum class ShaderType
{
    FRAGMENT,
    VERTEX
};

enum class ImageType
{
    RGBA,
    RGB
};

class Graphics : public EngineCore
{
public:
    Graphics();
    void Init() override;
    void Update() override;
    ~Graphics() override;
    void InitPVmatrices();
    void UpdatePVmatrices();
    void CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id);
    GLuint GetProgramHandle(const std::string& program_id);
    void LoadShader(const std::string& path, const std::string& id, ShaderType type);

    void AddTexture(const std::string& texture_id, unsigned texture);
    unsigned GetTexture(const std::string& texture_id);

    void AddMaterial(const std::string& material_id, Material* material);
    Material* GetMaterial(const std::string& material_id);


    void LoadTexture(const std::string& path, const std::string& texture_id, ImageType image_type);
    void loadObject(const std::string& path, const std::string& mesh_id);
    Mesh* GetMesh(const std::string& mesh_id);

    void AddSphereMesh();


    std::unordered_map<std::string, Material* > GetAllMaterial();
    std::unordered_map<std::string , Mesh*> GetAllMeshes();
    Camera camera;
private:
    std::unordered_map<std::string /*id*/, Material* /*material*/> materials;
    std::unordered_map<std::string /*id*/, Mesh* /*mesh*/> meshes;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, GLuint/*program handle*/> program_handles;
    std::unordered_map<std::string /*id*/, unsigned /*texture*/> textures;

    unsigned int uboMatrices = 0, uboLight = 0;

};
extern Graphics* GRAPHICS;
