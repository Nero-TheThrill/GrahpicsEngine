#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 lightcolor;
out vec3 lightposition;
out vec3 CamPos;

uniform mat4 model;

layout(std140, binding = 0) uniform GlobalMatrices
{
	mat4 projection;
	mat4 view;
}pv_matrices;

layout(std140, binding = 1) uniform GlobqalMatrices1
{
	vec3 position;
	vec4 color;
	vec3 campos;
}light;


void main()
{
	vec4 tmpFragPos=model*vec4(aPos,1.0);
	FragPos = vec3(tmpFragPos.x,tmpFragPos.y,tmpFragPos.z);
	gl_Position = pv_matrices.projection * pv_matrices.view * vec4(FragPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	Normal = aNormal;
	lightcolor=light.color;
	lightposition=light.position;
	CamPos=light.campos;
}