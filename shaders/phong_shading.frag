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
	float ambientStrength=0.1;
	vec3 I_a = ambientStrength * light.ambient;

	vec3 n_normal=normalize(Normal);
	vec3 light_vector = normalize(light.position-FragPosition);

	float diffuseStrength=1.5;
	vec3 I_d = diffuseStrength*light.diffuse*max(dot(n_normal,light_vector),0.0);

	float specularStrength=0.3;
	vec3 view_vector=normalize(view_position-FragPosition);
	vec3 reflectDirection = reflect(-light_vector,n_normal);
	vec3 I_s = specularStrength*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),32);

	vec3 I_local = attenuation*(I_a+I_d+I_s);
	float fog_factor=(far-length(view_position-FragPosition))/(far-near);
	return fog_factor*I_local+(1-fog_factor)*fog_color;
}

void main()
{
	vec3 result=vec3(0);
	for(int i=0;i<light_number;i++)
	{
		result+=CalculateLight(lights[i]);
	}
	//result=vec3(min(result.x,1.3),min(result.y,1.3),min(result.z,1.3));

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
			FragColor = texture(texture1,TexCoord)*vec4(result*global_ambient_color,1.0);
		else
			FragColor = vec4(result*global_ambient_color,1.0);
	}
	
}