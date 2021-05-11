#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 lightcolor;
in vec3 lightposition;
in vec3 Normal;
in vec3 FragPos;
in vec3 CamPos;

uniform sampler2D texture1;
uniform vec4 ourColor;

void main()
{    

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(lightcolor.x,lightcolor.y,lightcolor.z);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightposition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(lightcolor.x,lightcolor.y,lightcolor.z);

     // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(CamPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(lightcolor.x,lightcolor.y,lightcolor.z);  


    vec3 result = (ambient + diffuse + specular);
	FragColor =  vec4(result,1)*ourColor;
}//texture(texture1, TexCoord)