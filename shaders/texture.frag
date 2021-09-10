#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 objectColor;

void main()
{
	FragColor = texture(texture1, TexCoord)*vec4(objectColor,1.0);
}