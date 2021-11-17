#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 pos;
layout(std140, binding = 0) uniform GlobalMatrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;

void main()
{
	gl_Position = projection * mat4(mat3(view)) * vec4(aPos, 1.0);
	pos=aPos;
	TexCoord=aTexCoord;
}
