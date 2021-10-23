#version 450 core
out vec4 FragColor;

in vec3 resultColor;

uniform bool item_selected;

void main()
{
	
	if(item_selected)
	{
		FragColor = vec4(resultColor*vec3(1,0.3,0.3),1.0);		
	}
	else
	{
		FragColor = vec4(resultColor,1.0);
	}
}