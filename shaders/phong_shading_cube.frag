#version 450 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoord;
in vec3 pos;
in vec3 norm;
in vec3 t_norm;
in vec3 t_pos;

uniform bool item_selected;


uniform sampler2D top;
uniform sampler2D bottom;
uniform sampler2D left;
uniform sampler2D right;
uniform sampler2D front;
uniform sampler2D back;
uniform sampler2D emissive_texture;

uniform bool emissive_texture_exists;

uniform bool should_use_gpuside_uv;
uniform bool mapping_with_normal;
uniform int mapping_mode;
uniform bool isModePhongShading_EnvironmentMapping;
uniform float R;
uniform float G;
uniform float B;
uniform float RatioDenominator;
uniform int environmentmapping_mode;
float FresnelPower=5.0;
float F=((1.0-G)*(1.0-G))/((1.0+G)*(1.0+G));
vec3 RefractRGB,RefractR,RefractG,RefractB;
float fresnelRatio;
vec3 I;


uniform vec3 objectColor;

uniform float maxYval;
uniform float minYval;

uniform vec3 k_a;
uniform vec3 k_d;
uniform vec3 k_s;
uniform float ns;
uniform vec3 emissive;

vec3 n_normal=normalize(Normal);
vec2 realTexCoord,objectTexCoord;
vec3 I_a,I_d,I_s;
vec3 CurrentColor,CurrentColor1,resultColor;

struct Light
{
	uint type;    	   //            0
	vec3 direction;    // D,S        16
	vec3 position;     // P          32

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
	I_a= light.ambient*k_a;
	if(light.type==0)
	{
		vec3 light_vector = normalize(light.position-FragPosition);


		I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);



		vec3 view_vector=normalize(view_position-FragPosition);
		vec3 reflectDirection = 2*dot(n_normal,light_vector)*n_normal-light_vector;

		if(dot(n_normal,light_vector)>0.0)
		{

			I_s = k_s*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),ns)/10;
		}
		else
			I_s=vec3(0,0,0);
		
		float light_length=length(light.position-FragPosition);
		float attenuation=min(1/(light.c.x+light.c.y*light_length+light.c.z*light_length*light_length),1);
		vec3 I_local = attenuation*(I_a+I_d+I_s);
		return I_local;
	}
	else if(light.type==1)
	{
		vec3 light_vector = normalize(-light.direction);

		I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);

		vec3 view_vector=normalize(view_position-FragPosition);
		vec3 reflectDirection = 2*dot(n_normal,light_vector)*n_normal-light_vector;

		if(dot(n_normal,light_vector)>0.0)
		{
			I_s = k_s*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),ns)/10;
		}
		else
			I_s=vec3(0,0,0);

		vec3 I_local = (I_a+I_d+I_s);
		return I_local;
	}
	else
	{ 

		vec3 light_vector = normalize(light.position-FragPosition);


		I_d = k_d*light.diffuse*max(dot(n_normal,light_vector),0.0);


		vec3 view_vector=normalize(view_position-FragPosition);
		vec3 reflectDirection = 2*dot(n_normal,light_vector)*n_normal-light_vector;

		if(dot(n_normal,light_vector)>0.0)
		{
			I_s = k_s*light.specular*pow(max(dot(view_vector,reflectDirection),0.0),ns)/10;
		}
		else
			I_s=vec3(0,0,0);

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
		float attenuation=min(1/(light.c.x+light.c.y*light_length+light.c.z*light_length*light_length),1);
		vec3 I_local = attenuation*spotlighteffect*(I_d+I_s)+attenuation*I_a;
		return I_local;
	}
}

vec3 RefractCalculate(float ratio)
{
	float k=1.0-ratio*ratio*(1-dot(n_normal,I)*dot(n_normal,I));

	if(k<0.0)
		return vec3(0);
	else
		return ratio*I-(ratio*dot(n_normal,I)+sqrt(k))*n_normal;
}

vec3 GetTextureColor(vec3 v)
{
	vec3 tmpVec3=normalize(v),abstmpVec3=abs(tmpVec3);
	if (abstmpVec3.x >= abstmpVec3.y && abstmpVec3.x >= abstmpVec3.z)
    {
        if(tmpVec3.x < 0)
            realTexCoord.x = -tmpVec3.z/abstmpVec3.x;
        else
        	realTexCoord.x = tmpVec3.z/abstmpVec3.x;
        realTexCoord.y = tmpVec3.y/abstmpVec3.x;
        realTexCoord=(realTexCoord+vec2(1))/2;
	    if(tmpVec3.x>0)
	    	return vec3(texture(right,realTexCoord));
	    else
	    	return vec3(texture(left,realTexCoord));

	}
	if (abstmpVec3.y >= abstmpVec3.x && abstmpVec3.y >= abstmpVec3.z)
	{
	    if(tmpVec3.y < 0)
			realTexCoord.x = tmpVec3.x/abstmpVec3.y;
	    else
	    	realTexCoord.x = -tmpVec3.x/abstmpVec3.y;
	    realTexCoord.y = -tmpVec3.z/abstmpVec3.y;
	    realTexCoord=(realTexCoord+vec2(1))/2;
	    if(tmpVec3.y>0)
	    	return vec3(texture(top,realTexCoord));
	    else
	    	return vec3(texture(bottom,realTexCoord));
	}
	if (abstmpVec3.z >= abstmpVec3.y && abstmpVec3.z >= abstmpVec3.x)
	{
	    if(tmpVec3.z < 0) 
			realTexCoord.x = tmpVec3.x/abstmpVec3.z;
	    else
	    	realTexCoord.x = -tmpVec3.x/abstmpVec3.z;
	    realTexCoord.y = tmpVec3.y/abstmpVec3.z;
	    realTexCoord=(realTexCoord+vec2(1))/2;
	    if(tmpVec3.z>0)
	    	return vec3(texture(front,realTexCoord));
	    else
	    	return vec3(texture(back,realTexCoord));
	}

}
void main()
{
if(should_use_gpuside_uv)
	{
		vec3 tmpVec3,abstmpVec3;
		float u,v;
		if(mapping_with_normal)
			tmpVec3=normalize(t_norm);
		else
			tmpVec3=t_pos;
		abstmpVec3=abs(tmpVec3);
		switch(mapping_mode)
		{
			case 0:
				objectTexCoord=TexCoord;
				break;
			case 1:
			    u = degrees(atan(tmpVec3.z , tmpVec3.x));
    			u+=180;
   				v = 180-(acos(tmpVec3.y / (sqrt(tmpVec3.x * tmpVec3.x + tmpVec3.y * tmpVec3.y + tmpVec3.z * tmpVec3.z))) * 180.f / acos(-1)) ;
           
				objectTexCoord = vec2(u / 360.f, v / 180.f);
				break;
			case 2:
			    u = degrees(atan(tmpVec3.z , tmpVec3.x));
				u+=180;
   				v = (tmpVec3.y-minYval)/(maxYval-minYval);
   				objectTexCoord = vec2(u/360.f,v);
   				break;
   			case 3:
           		if (abstmpVec3.x >= abstmpVec3.y && abstmpVec3.x >= abstmpVec3.z)
            	{
                	if(tmpVec3.x < 0)
                		objectTexCoord.x = tmpVec3.z/abstmpVec3.x;
                	else
                		objectTexCoord.x = -tmpVec3.z/abstmpVec3.x;
                	objectTexCoord.y = tmpVec3.y/abstmpVec3.x;
	            }
	            if (abstmpVec3.y >= abstmpVec3.x && abstmpVec3.y >= abstmpVec3.z)
	            {
	                if(tmpVec3.y < 0)
	                	objectTexCoord.x = tmpVec3.x/abstmpVec3.y;
	                else
	                	objectTexCoord.x = -tmpVec3.x/abstmpVec3.y;
	                objectTexCoord.y = tmpVec3.z/abstmpVec3.y;
	            }
	            if (abstmpVec3.z >= abstmpVec3.y && abstmpVec3.z >= abstmpVec3.x)
	            {
	                if(tmpVec3.z < 0) 
	                	objectTexCoord.x = -tmpVec3.x/abstmpVec3.z;
	                else
	                	objectTexCoord.x = tmpVec3.x/abstmpVec3.z;
	                objectTexCoord.y = tmpVec3.y/abstmpVec3.z;
	            }
	            objectTexCoord=(objectTexCoord+vec2(1))/2;
   				break;
   			default:
   				break;
		}
	}
	else
		objectTexCoord=TexCoord;


	I = normalize(FragPosition - view_position);
	vec3 reflectDirection = I-2*dot(n_normal,I)*n_normal;

	fresnelRatio=F + (1.0 - F) * pow((1.0 - dot(-I,n_normal)), FresnelPower);
	RefractR=RefractCalculate(R);
	RefractG=RefractCalculate(G);
	RefractB=RefractCalculate(B);
	RefractRGB.r=GetTextureColor(RefractR).r;
	RefractRGB.g=GetTextureColor(RefractG).g;
	RefractRGB.b=GetTextureColor(RefractB).b;
	float ratio=1/RatioDenominator;

	vec3 refractDirection;
	refractDirection=RefractCalculate(ratio);


	CurrentColor=GetTextureColor(reflectDirection);
	CurrentColor1=GetTextureColor(refractDirection);
  	
	if(environmentmapping_mode==0)
		resultColor = CurrentColor;
	else if(environmentmapping_mode==1)
		resultColor = CurrentColor1;
	else //if(environmentmapping_mode==2)
		resultColor = mix(RefractRGB,CurrentColor,fresnelRatio);


	vec3 result=vec3(0);
	for(int i=0;i<light_number;i++)
	{
		result+=CalculateLight(lights[i]);
	}
	if(emissive_texture_exists)
		result+=global_ambient_color*k_a+vec3(texture(emissive_texture,objectTexCoord))/5;
	else
		result+=global_ambient_color*k_a+emissive;
	float fog_factor=(far-length(view_position-FragPosition))/(far-near);
	result =  fog_factor*result+(1-fog_factor)*fog_color;
	result=vec3(min(result.x,1),min(result.y,1),min(result.z,1));

	if(item_selected)
	{
		FragColor = vec4(result*vec3(1,0.3,0.3),1.0);		
	}
	else
	{
		if(isModePhongShading_EnvironmentMapping)
		{	
			FragColor=vec4(mix(result,resultColor,0.7),1.0);
			
		}
		else
		{
			FragColor = vec4(resultColor,1.0);
		}

	}
}