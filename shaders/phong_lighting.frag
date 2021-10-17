#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoord;
in vec3 resultColor;
uniform bool item_selected;
uniform bool texture_exists;
uniform sampler2D texture1;
uniform vec3 objectColor;


void main()
{
	
	if(item_selected)
	{
		if(texture_exists)
			FragColor = texture(texture1,TexCoord)*vec4(resultColor*vec3(1,0.3,0.3),0.5);
		else
			FragColor = vec4(resultColor*vec3(1,0.3,0.3),0.5);
	}
	else
	{
		if(texture_exists)
			FragColor = texture(texture1,TexCoord)*vec4(resultColor,1.0);
		else
			FragColor = vec4(resultColor,1.0);
	}
}