#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D default_texture;

void main()
{
	FragColor=texture(default_texture,TexCoord)*vec4(0.5,0.5,0.5,1);
}