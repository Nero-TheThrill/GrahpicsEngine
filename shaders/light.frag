#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;

//uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

float ambientStrength=0.1;
float specularStrength=0.3;
vec3 ambient = ambientStrength * lightColor;
vec3 norm=normalize(Normal);
vec3 lightDirection = normalize(lightPosition-FragPosition);
vec3 viewDirection=normalize(viewPosition-FragPosition);
vec3 reflectDirection = reflect(-lightDirection,norm);
float spec=pow(max(dot(viewDirection,reflectDirection),0.0),64);
vec3 specular = specularStrength*spec*lightColor;
float diff=max(dot(norm,lightDirection),0.0);
vec3 diffuse = diff*lightColor;

void main()
{
	FragColor = vec4((ambient+diffuse+specular)*objectColor,1.0);
}