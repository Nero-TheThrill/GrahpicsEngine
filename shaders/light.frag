#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform bool item_selected;

uniform float k_d;
uniform vec3 emissive;

vec3 I_d;
vec3 n_normal=normalize(Normal);

struct Light
{
	uint type;    //            0
	vec3 direction;    // D,S          16
	vec3 position;     // P        32

	vec3 ambient;      // D,P,S      48
	vec3 diffuse;      // D,P,S      64
	vec3 specular;     // D,P,S      80
	vec3 c;
	float inner_angle; // S          96
	float outer_angle; // S          112
	float falloff;     // S          128
};

layout(std140, binding = 1) uniform LightInformation
{	
	uint light_number;
	float near;
	float far;	
	vec3 view_position;
	vec3 fog_color;
	vec3 global_ambient_color;
	Light lights[16];
};

vec3 CalculateLight(Light light)
{
	if(light.type==0)
	{

		vec3 light_vector = normalize(light.position-FragPosition);
		I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);

		return I_d;
	}
	else if(light.type==1)
	{
		vec3 light_vector = normalize(light.direction);
		I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);
		return I_d;
	}
	else
	{
		vec3 light_vector = normalize(light.position-FragPosition);
		I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);
		return I_d;
	}
}

void main()
{
	vec3 result=vec3(0);
	for(int i=0;i<light_number;i++)
	{
		result+=CalculateLight(lights[i]);
	}
	result+=emissive;
	if(item_selected)
	{
			FragColor = vec4(vec3(1,0.3,0.3),0.5);
	}
	else
	{
			FragColor = vec4(result*objectColor,1.0);
	}
}