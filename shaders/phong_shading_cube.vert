#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPosition;
out vec2 TexCoord;
out vec3 pos;
out vec3 norm;
out vec3 t_norm;
out vec3 t_pos;

layout(std140, binding = 0) uniform ProjectViewMatrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	Normal=mat3(transpose(inverse(model))) * aNormal;  
	FragPosition=vec3(model*vec4(aPos,1.0));
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	pos=vec3(model * vec4(aPos, 1.0));
	norm=vec3(model * vec4(aNormal, 1.0));
	t_norm=aNormal;
	t_pos=aPos;
}
