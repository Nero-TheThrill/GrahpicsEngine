#include "ObjectLoader.h"

#include "Graphics.h"


void ObjectLoader::loadObject(const std::string& path, const std::string& mesh_id)
{
    tmp_positions.clear();
    tmp_normals.clear();
    tmp_texcoords.clear();

    tmp_positions_indices.clear();
    tmp_normal_indices.clear();
    tmp_texture_indices.clear();

    pos_texcoord_norm_indices.clear();

    bool using_group = false;
    int vertexcount = 0;

    meshgroup = new MeshGroup();
    mesh = new ModelMesh();


    meshgroup->AddMesh(mesh);
    meshgroup->name = mesh_id;
    mesh->name = mesh_id;

    std::ifstream in_file(path);
    std::string line = "";



    if (!in_file.is_open())
    {
        std::cout << "failed to load file : " << path << std::endl;
    }

    min_val_x = FLT_MAX;
    max_val_x = FLT_MIN;
    max_val_y = max_val_x, min_val_y = min_val_x;
    max_val_z = max_val_x, min_val_z = min_val_x;

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
        else if (prefix == "o" || prefix == "g") // 
        {
            if (using_group)
            {
                reArrangeData();

                tmp_positions_indices.clear();
                tmp_normal_indices.clear();
                tmp_texture_indices.clear();
                pos_texcoord_norm_indices.clear();

                mesh = new ModelMesh();
                ss >> prefix;
                mesh->name = prefix;
                meshgroup->AddMesh(mesh);
            }
            else
            {
                using_group = true;
                ss >> prefix;
                mesh->name = prefix;
            }
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
            tmp_positions.push_back(tmp_vec3);
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
            tmp_texcoords.push_back(tmp_vec2);
        }
        else if (prefix == "vn") // normal
        {
            ss >> tmp_vec3.x >> tmp_vec3.y >> tmp_vec3.z;
            tmp_normals.push_back(tmp_vec3);
        }
        else if (prefix == "f") // faces
        {
            ss >> tmp_glInt_p1;

            if (ss.peek() == '/')
            {
                ss.ignore(1, '/');
                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    ss >> tmp_glInt_n1; // normal indices
                    tmp_normal_indices.push_back(tmp_glInt_n1 - 1);
                }
                else
                {
                    ss >> tmp_glInt_t1;// should be texture indices or normal indices
                    if (ss.peek() == '/')
                    {
                        tmp_texture_indices.push_back(tmp_glInt_t1 - 1);
                        ss.ignore(1, '/');
                        ss >> tmp_glInt_n1; // normal indices
                        tmp_normal_indices.push_back(tmp_glInt_n1 - 1);
                    }
                    else
                    {
                        tmp_texture_indices.push_back(tmp_glInt_t1 - 1);
                    }
                }
            }
            tmp_positions_indices.push_back(tmp_glInt_p1 - 1);
            ss >> tmp_glInt_p2;
            if (ss.peek() == '/')
            {
                ss.ignore(1, '/');
                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    ss >> tmp_glInt_n2; // normal indices
                    tmp_normal_indices.push_back(tmp_glInt_n2 - 1);
                }
                else
                {
                    ss >> tmp_glInt_t2;// should be texture indices or normal indices
                    if (ss.peek() == '/')
                    {
                        tmp_texture_indices.push_back(tmp_glInt_t2 - 1);
                        ss.ignore(1, '/');
                        ss >> tmp_glInt_n2; // normal indices
                        tmp_normal_indices.push_back(tmp_glInt_n2 - 1);
                    }
                    else
                    {
                        tmp_texture_indices.push_back(tmp_glInt_t2 - 1);
                    }
                }
            }
            tmp_positions_indices.push_back(tmp_glInt_p2 - 1);
            ss >> tmp_glInt_p3;
            if (ss.peek() == '/')
            {
                ss.ignore(1, '/');
                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    ss >> tmp_glInt_n3; // normal indices
                    tmp_normal_indices.push_back(tmp_glInt_n3 - 1);
                }
                else
                {
                    ss >> tmp_glInt_t3;// should be texture indices or normal indices
                    if (ss.peek() == '/')
                    {
                        tmp_texture_indices.push_back(tmp_glInt_t3 - 1);
                        ss.ignore(1, '/');
                        ss >> tmp_glInt_n3; // normal indices
                        tmp_normal_indices.push_back(tmp_glInt_n3 - 1);
                    }
                    else
                    {
                        tmp_texture_indices.push_back(tmp_glInt_t3 - 1);
                    }
                }
            }
            tmp_positions_indices.push_back(tmp_glInt_p3 - 1);
            tmp_glInt_p2 = tmp_glInt_p3;
            tmp_glInt_n2 = tmp_glInt_n3;
            tmp_glInt_t2 = tmp_glInt_t3;
            while (ss >> tmp_glInt_p3)
            {
                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    if (ss.peek() == '/')
                    {
                        ss.ignore(1, '/');
                        ss >> tmp_glInt_n3; // normal indices
                        tmp_normal_indices.push_back(tmp_glInt_n1 - 1);
                        tmp_normal_indices.push_back(tmp_glInt_n2 - 1);
                        tmp_normal_indices.push_back(tmp_glInt_n3 - 1);
                        tmp_glInt_n2 = tmp_glInt_n3;
                    }
                    else
                    {
                        ss >> tmp_glInt_t3;// should be texture indices or normal indices
                        if (ss.peek() == '/')
                        {
                            tmp_texture_indices.push_back(tmp_glInt_t1 - 1);
                            tmp_texture_indices.push_back(tmp_glInt_t2 - 1);
                            tmp_texture_indices.push_back(tmp_glInt_t3 - 1);
                            tmp_glInt_t2 = tmp_glInt_t3;
                            ss.ignore(1, '/');
                            ss >> tmp_glInt_n3; // normal indices
                            tmp_normal_indices.push_back(tmp_glInt_n1 - 1);
                            tmp_normal_indices.push_back(tmp_glInt_n2 - 1);
                            tmp_normal_indices.push_back(tmp_glInt_n3 - 1);
                            tmp_glInt_n2 = tmp_glInt_n3;
                        }
                        else
                        {
                            tmp_texture_indices.push_back(tmp_glInt_t1 - 1);
                            tmp_texture_indices.push_back(tmp_glInt_t2 - 1);
                            tmp_texture_indices.push_back(tmp_glInt_t3 - 1);
                            tmp_glInt_t2 = tmp_glInt_t3;
                        }
                    }
                }
                tmp_positions_indices.push_back(tmp_glInt_p1 - 1);
                tmp_positions_indices.push_back(tmp_glInt_p2 - 1);
                tmp_positions_indices.push_back(tmp_glInt_p3 - 1);
                tmp_glInt_p2 = tmp_glInt_p3;
            }

        }
        else
        {

        }
    }

    reArrangeData();

    reSizeObject();

    meshgroup->Init();
    GRAPHICS->AddMeshGroup(mesh_id,meshgroup);
}

void ObjectLoader::reArrangeData()
{
    int iter = 0;

    if (tmp_normal_indices.empty() && tmp_texture_indices.empty())
    {
        mesh->positions_use_indices = tmp_positions;
        mesh->indices = tmp_positions_indices;
    }
    else if (tmp_normal_indices.empty())
    {
        for (int i = 0; i < tmp_positions_indices.size(); i++)
        {
            glm::ivec3 key = glm::ivec3(tmp_positions_indices[i], tmp_texture_indices[i], 0);
            if (pos_texcoord_norm_indices.find(key) == pos_texcoord_norm_indices.end())
            {
                mesh->positions_use_indices.push_back(tmp_positions[tmp_positions_indices[i]]);
                mesh->texcoords_use_indices.push_back(tmp_texcoords[tmp_texture_indices[i]]);
                mesh->indices.push_back(iter);
                pos_texcoord_norm_indices.insert(std::pair<glm::ivec3, int>(key, iter));
                iter++;
            }
            else
            {
                mesh->indices.push_back(pos_texcoord_norm_indices[key]);
            }

        }
    }
    else if (tmp_texture_indices.empty())
    {
        for (int i = 0; i < tmp_positions_indices.size(); i++)
        {
            glm::ivec3 key = glm::ivec3(tmp_positions_indices[i], 0, tmp_normal_indices[i]);
            if (pos_texcoord_norm_indices.find(key) == pos_texcoord_norm_indices.end())
            {
                mesh->positions_use_indices.push_back(tmp_positions[tmp_positions_indices[i]]);
                mesh->vertex_normals.push_back(tmp_normals[tmp_normal_indices[i]]);
                mesh->indices.push_back(iter);
                pos_texcoord_norm_indices.insert(std::pair<glm::ivec3, int>(key, iter));
                iter++;
            }
            else
            {
                mesh->indices.push_back(pos_texcoord_norm_indices[key]);
            }

        }
    }
    else
    {
        for (int i = 0; i < tmp_positions_indices.size(); i++)
        {
            glm::ivec3 key = glm::ivec3(tmp_positions_indices[i], tmp_texture_indices[i], tmp_normal_indices[i]);
            if (pos_texcoord_norm_indices.find(key) == pos_texcoord_norm_indices.end())
            {
                mesh->positions_use_indices.push_back(tmp_positions[tmp_positions_indices[i]]);
                mesh->vertex_normals.push_back(tmp_normals[tmp_normal_indices[i]]);
                mesh->texcoords_use_indices.push_back(tmp_texcoords[tmp_texture_indices[i]]);
                mesh->indices.push_back(iter);
                pos_texcoord_norm_indices.insert(std::pair<glm::ivec3, int>(key, iter));
                iter++;
            }
            else
            {
                mesh->indices.push_back(pos_texcoord_norm_indices[key]);
            }
        }
    }
}

void ObjectLoader::reSizeObject()
{
    float gap_x = max_val_x - min_val_x;
    float gap_y = max_val_y - min_val_y;
    float gap_z = max_val_z - min_val_z;
    float denominator = std::max(std::max(gap_x, gap_y), gap_z) / 2.f;

    float subtract_x = gap_x / 2.f + min_val_x;
    float subtract_y = gap_y / 2.f + min_val_y;
    float subtract_z = gap_z / 2.f + min_val_z;
    
    for (auto m_mesh : meshgroup->model_meshes)
    {
        int iterator = 0;
        for (auto p : m_mesh->positions_use_indices)
        {
            m_mesh->positions_use_indices[iterator] = glm::vec3((p.x - subtract_x) / denominator, (p.y - subtract_y) / denominator, (p.z - subtract_z) / denominator);
            iterator++;
        }
    }
}
