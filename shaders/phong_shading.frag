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

struct DirLight {
    vec3 direction;

	//color
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

	//color
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    
    float inner_angle;
    float outer_angle;
    float falloff;
    //color
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


layout(std140, binding = 1) uniform LightInformation
{
	uint active_lights;
	vec3 fog_color;
	vec3 ambient_color;

	//attenuation
    float constant;
    float linear;
    float quadratic;
};

void main()
{
	float ambientStrength=0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm=normalize(Normal);
	vec3 lightDirection = normalize(lightPosition-FragPosition);
	float diff=max(dot(norm,lightDirection),0.0);
	vec3 diffuse = diff*lightColor;

	float specularStrength=0.2;
	vec3 viewDirection=normalize(viewPosition-FragPosition);
	vec3 reflectDirection = reflect(-lightDirection,norm);
	float spec=pow(max(dot(viewDirection,reflectDirection),0.0),32);
	vec3 specular = specularStrength*spec*lightColor;

	if(item_selected)
	{
		if(texture_exists)
			FragColor = texture(texture1,TexCoord)*vec4((ambient+diffuse+specular)*vec3(1,0.3,0.3),1.0);
		else
			FragColor = vec4((ambient+diffuse+specular)*vec3(1,0.3,0.3),1.0);
	}
	else
	{
		if(texture_exists)
			FragColor = texture(texture1,TexCoord)*vec4((ambient+diffuse+specular)*objectColor,1.0);
		else
			FragColor = vec4((ambient+diffuse+specular)*objectColor,1.0);
	}
}