#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoord;

uniform bool item_selected;
uniform bool texture_exists;
uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;


struct Light
{
	uint lighttype;    //            0
	vec3 direction;    // D          16
	vec3 position;     // P,S        32

	vec3 ambient;      // D,P,S      48
	vec3 diffuse;      // D,P,S      64
	vec3 specular;     // D,P,S      80

	float inner_angle; // S          96
	float outer_angle; // S          112
	float falloff;     // S          128
};

layout(std140, binding = 1) uniform LightInformation
{	
	uint light_number;	
	vec3 view_position;
	vec3 fog_color;
	vec3 global_ambient_color;
	float near;
	float far;
	float attenuation;
	Light lights[16];
};

vec3 CalculateLight(Light light)
{
	float ambientStrength=0.05;
	vec3 ambient = ambientStrength * light.ambient;

	vec3 norm=normalize(Normal);
	vec3 light_vector = normalize(light.position-FragPosition);
	float diff=max(dot(norm,light_vector),0.0);
	vec3 diffuse = diff*light.diffuse;

	float specularStrength=0.2;
	vec3 viewDirection=normalize(view_position-FragPosition);
	vec3 reflectDirection = reflect(-light_vector,norm);
	float spec=pow(max(dot(viewDirection,reflectDirection),0.0),32);
	vec3 specular = specularStrength*spec*light.specular;
	return (ambient+diffuse+specular);
}

void main()
{
	vec3 result=vec3(0);
	for(int i=0;i<light_number;i++)
	{
		result+=CalculateLight(lights[i]);
	}


	if(item_selected)
	{
		if(texture_exists)
			FragColor = texture(texture1,TexCoord)*vec4(result*vec3(1,0.3,0.3),0.5);
		else
			FragColor = vec4(result*vec3(1,0.3,0.3),0.5);
	}
	else
	{
		if(texture_exists)
			FragColor = texture(texture1,TexCoord)*vec4(result*objectColor,1.0);
		else
			FragColor = vec4(result*objectColor,1.0);
	}
	
}