#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;




void main()
{
	vec3 norm=normalize(Normal);
	vec3 lightDirection = normalize(lightPosition-FragPosition);
	float diff=max(dot(norm,lightDirection),0.0);
	vec3 diffuse = diff*lightColor;

	FragColor = vec4((diffuse)*objectColor,1.0);
}