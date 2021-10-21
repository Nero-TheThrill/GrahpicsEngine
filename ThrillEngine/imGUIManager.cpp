#include "imGUIManager.h"
#include <iostream>
#include "Graphics.h"
#include "ObjectManager.h"
#include "imgui/imgui_impl_opengl3.h"

imGUIManager* IMGUIMANAGER = nullptr;

imGUIManager::imGUIManager(GLFWwindow* window)
{
    IMGUIMANAGER = this;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
    light_type[0] = "POINT";
    light_type[1] = "DIRECTIONAL";
    light_type[2] = "SPOT";
    std::cout << "imGUI Initialize" << std::endl;
}

void imGUIManager::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {
        ImGui::Begin("GraphicsEngine GUI");

        if (ImGui::Button("Reload Shader"))
            GRAPHICS->ReLoadShader();
        ImGui::SameLine();
        if (ImGui::Button("Unselect All"))
        {
            if (current_item != nullptr)
                current_item->item_selected = false;
            if (current_light != nullptr)
                current_light->item_selected = false;
            current_light = nullptr;
            current_item = nullptr;
            
        }
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
      
        /* glm::vec3 bgcolor=GRAPHICS->background_color;
         ImGui::DragFloat3("background color", glm::value_ptr(bgcolor), 0.01f, 0, 1);
         GRAPHICS->SetBackgroundColor(glm::vec4(bgcolor, 1.0f));*/
        

        std::unordered_map<unsigned, Object*> objects = OBJECTMANAGER->GetAllObjects();

        if (ImGui::BeginCombo("select object", current_item != nullptr ? current_item->name.c_str() : ""))
        {

            prev_item = current_item;

            for (auto obj : objects)
            {
                if (obj.second != nullptr)
                {
                    bool is_selected = (current_item == obj.second);
                    if (ImGui::Selectable(obj.second->name.c_str(), is_selected))
                    {
                        current_item = obj.second;
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();

                }
            }
            if (current_item != prev_item)
            {
                if (prev_item != nullptr)
                {
                    prev_item->item_selected = false;
                }
                if (current_item != nullptr)
                {
                    current_item->item_selected = true;
                }

            }
            ImGui::EndCombo();
        }
        if (current_item != nullptr)
        {
            glm::vec3 pos = current_item->transform.position;
            ImGui::DragFloat3("translation", glm::value_ptr(pos), 0.1f, -FLT_MAX, FLT_MAX);
            current_item->transform.Translate(pos);

            glm::vec3 scale = current_item->transform.current_scale;
            ImGui::DragFloat3("scale", glm::value_ptr(scale), 0.1f, -FLT_MAX, FLT_MAX);
            current_item->transform.Scale(scale);

            glm::vec3 rotate = current_item->transform.current_rotate_axis;
            float degree = current_item->transform.current_rotate_degree;
            ImGui::DragFloat3("rotate axis", glm::value_ptr(rotate), 0.01f, -1, 1);
            ImGui::DragFloat("degree", &degree);
            current_item->transform.Rotate(degree, rotate);

            std::unordered_map < std::string, std::pair<Shader, std::pair<std::string, std::string>>> shaders = GRAPHICS->GetAllShaders();
            std::string current_shader = current_item->shader.name;

            if (ImGui::BeginCombo("select shader", current_shader.c_str()))
            {
                for (auto shader : shaders)
                {
                    bool is_selected = (current_shader == shader.second.first.name);
                    if (ImGui::Selectable(shader.second.first.name.c_str(), is_selected))
                    {
                        current_shader = shader.second.first.name;
                        current_item->SetShader(shader.second.first.name);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            std::unordered_map<std::string, MeshGroup*> meshes = GRAPHICS->GetAllMeshGroups();
            std::string current_mesh = current_item->mesh->name;
            if (ImGui::BeginCombo("select mesh", current_mesh.c_str()))
            {
                for (auto mesh : meshes)
                {
                    bool is_selected = (current_mesh == mesh.second->name);
                    if (ImGui::Selectable(mesh.second->name.c_str(), is_selected))
                    {
                        current_mesh = mesh.second->name;
                        current_item->SetMeshGroup(mesh.second);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            int mode = current_item->drawmode;
            ImGui::RadioButton("face normal", &mode, 0); ImGui::SameLine();
            ImGui::RadioButton("vertex normal", &mode, 1);
            current_item->drawmode = mode;
            bool drawnormal = current_item->shouldDrawNormals;
            ImGui::Checkbox("draw normals", &drawnormal);
            current_item->shouldDrawNormals = drawnormal;
        }

        ImGui::End();
    }

    {
        ImGui::Begin("Light Manager");
        prev_lightNumber = lightNumber;
        ImGui::SliderInt("light number", &lightNumber, 1, 16);
        if (prev_lightNumber != lightNumber)
        {
            lightNumberChanged = true;
            if (current_item != nullptr)
                current_item->item_selected = false;
            current_light = nullptr;
            current_item = nullptr;
        }

        ImGui::Checkbox("Rotate lights", &shouldRotatelight);
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();

        ImGui::RadioButton("light option a", &lightoption, 0); ImGui::SameLine();
        ImGui::RadioButton("light option b", &lightoption, 1); ImGui::SameLine();
        ImGui::RadioButton("light option c", &lightoption, 2);
        std::unordered_map<unsigned, LightObject*> lights = OBJECTMANAGER->GetAllLights();
        if(lightoption==0&&!lights.empty())
        {
            if (ImGui::BeginCombo("all light type", light_type[static_cast<int>(lights.begin()->second->type)].c_str()))
            {
                for (int i = 0; i < 3; i++)
                {
                    bool is_selected = (i == static_cast<int>(lights.begin()->second->type));
                    if (ImGui::Selectable(light_type[i].c_str(), is_selected))
                    {
                        for (auto light : lights)
                            light.second->type = static_cast<LightType>(i);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            for (auto light : lights)
            {
                light.second->ambient = glm::vec3(0.7f,0.7f,1.0f);
                light.second->diffuse = glm::vec3(1,1,1);
                light.second->specular = glm::vec3(1, 1, 1);
            }
        }
        else if(lightoption==1&&!lights.empty())
        {
            if (ImGui::BeginCombo("all light type", light_type[static_cast<int>(lights.begin()->second->type)].c_str()))
            {
                for (int i = 0; i < 3; i++)
                {
                    bool is_selected = (i == static_cast<int>(lights.begin()->second->type));
                    if (ImGui::Selectable(light_type[i].c_str(), is_selected))
                    {
                        for (auto light : lights)
                            light.second->type = static_cast<LightType>(i);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            int iter = 1;
            for (auto light : lights)
            {
                if (iter % 2 == 0)
                {
                    light.second->ambient = glm::vec3(0.3f, 0.5f,1.f);
                    light.second->diffuse = glm::vec3(0.3f, 0.5f, 1.f);
                    light.second->specular = glm::vec3(0.3f, 0.5f, 1.f);
                }
                else
                {
                    light.second->ambient = glm::vec3(1.f, 0.5f, 0.3f);
                    light.second->diffuse = glm::vec3(1.f, 0.5f, 0.3f);
                    light.second->specular = glm::vec3(1.f, 0.5f, 0.3f);
                }
                iter += 1;
            }
        }
        else
        {
            
        }

        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();

      

        if (ImGui::BeginCombo("select light", current_light != nullptr ? current_light->name.c_str() : ""))
        {
            prev_light = current_light;
            for (auto light : lights)
            {
                if (light.second != nullptr)
                {
                    bool is_selected = (current_light == light.second);
                    if (ImGui::Selectable(light.second->name.c_str(), is_selected))
                    {
                        current_light = light.second;
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
            }
            if (current_light != prev_light)
            {
                if (prev_light != nullptr)
                {
                    prev_light->item_selected = false;
                }
                if (current_light != nullptr)
                {
                    current_light->item_selected = true;
                }

            }
            ImGui::EndCombo();
        }
        if (current_light != nullptr)
        {
            if (ImGui::BeginCombo("light type", light_type[static_cast<int>(current_light->type)].c_str()))
            {
                for (int i = 0; i < 3; i++)
                {
                    bool is_selected = (i == static_cast<int>(current_light->type));
                    if (ImGui::Selectable(light_type[i].c_str(), is_selected))
                    {
                        current_light->type = static_cast<LightType>(i);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            if (current_light->type == LightType::SPOT)
            {
                float inner_radian = current_light->inner_angle;
                ImGui::DragFloat("inner_angle(radian)", &inner_radian, 0.001f,0,current_light->outer_angle-0.001f);
                current_light->inner_angle=inner_radian;

                float outer_radian = current_light->outer_angle;
                ImGui::DragFloat("outer_angle(radian)", &outer_radian, 0.001f,0.01f,1.57f);
                current_light->outer_angle = outer_radian;
                if(current_light->outer_angle<current_light->inner_angle)
                {
                    current_light->inner_angle = current_light->outer_angle-0.001f;
                }
                float falloff_val = current_light->falloff;
                ImGui::DragFloat("falloff value", &falloff_val,0.001f,0,1);
                current_light->falloff = falloff_val;
            }
        }
    ImGui::End();
    }
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imGUIManager::Init()
{
    lightNumberChanged = true;
    current_light = nullptr;
    current_item = nullptr;
    prev_item = nullptr;
    shouldRotatelight = true;
    lightNumber = 1;
}

imGUIManager::~imGUIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "imGUIManager Destructor Called" << std::endl;
}
