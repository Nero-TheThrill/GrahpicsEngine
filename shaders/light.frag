#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

//uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;




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

	FragColor = vec4((ambient+diffuse+specular)*objectColor,1.0);
}