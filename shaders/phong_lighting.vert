#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPosition;
out vec2 TexCoord;
out vec3 resultColor;
layout(std140, binding = 0) uniform ProjectViewMatrices
{
	mat4 projection;
	mat4 view;
};

float k_a=0.1;
float k_d=0.25;
float k_s=0.1;
struct Light
{
	uint type;    //            0
	vec3 direction;    // D,S          16
	vec3 position;     // P        32

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
	float near;
	float far;	
	vec3 view_position;
	vec3 fog_color;
	vec3 global_ambient_color;
	vec3 c;
	Light lights[16];
};

uniform mat4 model;
vec3 CalculateLight(Light light)
{
	if(light.type==0)
	{
		vec3 I_a = k_a * light.ambient;

		vec3 n_normal=normalize(Normal);
		vec3 light_vector = normalize(light.position-FragPosition);

		vec3 I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);

		vec3 view_vector=normalize(view_position-FragPosition);
		vec3 reflectDirection = reflect(-light_vector,n_normal);
		vec3 I_s = k_s*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),32);

		
		float light_length=length(light.position-FragPosition);
		float attenuation=min(1/(c.x+c.y*light_length+c.z*light_length*light_length),1);
		vec3 I_local = attenuation*(I_a+I_d+I_s);
		return I_local;
	}
	else if(light.type==1)
	{
		vec3 I_a = k_a * light.ambient;

		vec3 n_normal=normalize(Normal);
		vec3 light_vector = normalize(light.direction);

		vec3 I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);

		vec3 view_vector=normalize(view_position-FragPosition);
		vec3 reflectDirection = reflect(-light_vector,n_normal);
		vec3 I_s = k_s*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),32);

		vec3 I_local = (I_a+I_d+I_s);
		return I_local;
	}
	else
	{
		
		vec3 I_a = k_a * light.ambient;

		vec3 n_normal=normalize(Normal);
		vec3 light_vector = normalize(light.position-FragPosition);

		vec3 I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);

		vec3 view_vector=normalize(view_position-FragPosition);
		vec3 reflectDirection = reflect(-light_vector,n_normal);
		vec3 I_s = k_s*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),32);


		float alpha = dot(-light_vector, normalize(light.direction)); 
    	float spotlighteffect=0;
    	if(alpha<cos(light.outer_angle))
    	{
    		spotlighteffect=0;
    	}
    	else if(alpha>cos(light.inner_angle))
    	{
    		spotlighteffect=1;
    	}
    	else
    	{
    		spotlighteffect=pow((alpha-cos(light.outer_angle))/(cos(light.inner_angle)-cos(light.outer_angle)),light.falloff);
    	}
		float light_length=length(light.position-FragPosition);
		float attenuation=min(1/(c.x+c.y*light_length+c.z*light_length*light_length),1);
		vec3 I_local = attenuation*spotlighteffect*(I_d+I_s)+attenuation*I_a;
		return I_local;
	}
}

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	Normal=mat3(transpose(inverse(model))) * aNormal;  
	FragPosition=vec3(model*vec4(aPos,1.0));
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	vec3 result=vec3(0);
	for(int i=0;i<light_number;i++)
	{
		result+=CalculateLight(lights[i]);
	}
	result+=global_ambient_color*k_a;
	float fog_factor=(far-length(view_position-FragPosition))/(far-near);
	result =  fog_factor*result+(1-fog_factor)*fog_color;
	result=vec3(min(result.x,1),min(result.y,1),min(result.z,1));

	resultColor=result;
}
