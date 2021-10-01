#pragma once
#include <vector>
#include "EngineCore.h"
#include "Object.h"
#include <unordered_map>
#include "stb_image.h"
#include "Camera.h"
#include "MeshGroup.h"

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
    Shader GetShader(const std::string& id);
    void LoadShader(const std::string& path, const std::string& id, ShaderType type);

    void AddTexture(const std::string& texture_id, unsigned texture);
    unsigned GetTexture(const std::string& texture_id);

    void AddMaterial(const std::string& material_id, Material* material);
    Material* GetMaterial(const std::string& material_id);

    void LoadTexture(const std::string& path, const std::string& texture_id, ImageType image_type);

    MeshGroup* GetMeshGroup(const std::string& mesh_id);
    void AddMeshGroup(const std::string& mesh_id, MeshGroup* mesh_group);

    void AddSphereMesh();

    void SetBackgroundColor(glm::vec4 bgcolor);

    void SetLightObject(Object* obj);


    glm::vec4 background_color = glm::vec4(0.61f, 0.61f, 0.9f, 1.0f);
    std::unordered_map<std::string, Material* > GetAllMaterial();
    std::unordered_map<std::string , MeshGroup*> GetAllMeshGroups();
    std::unordered_map<std::string, Shader> GetAllShaders();
    Camera camera;
    Object* light=nullptr;
private:
    std::unordered_map<std::string /*id*/, Material* /*material*/> materials;
    std::unordered_map<std::string /*id*/, MeshGroup* /*mesh*/> meshgroups;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, Shader/*shader*/> shaders;
    std::unordered_map<std::string /*id*/, unsigned /*texture*/> textures;

    unsigned int uboMatrices = 0;


};

inline void Graphics::AddMeshGroup(const std::string& mesh_id, MeshGroup* mesh_group)
{
    meshgroups.insert(std::pair<std::string, MeshGroup*>(mesh_id, mesh_group));
}

extern Graphics* GRAPHICS;
