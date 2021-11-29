#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 pos;

uniform sampler2D top;
uniform sampler2D bottom;
uniform sampler2D left;
uniform sampler2D right;
uniform sampler2D front;
uniform sampler2D back;


vec2 realTexCoord;

void main()
{           		
	vec3 tmpVec3=pos,abstmpVec3=abs(tmpVec3);
	if (abstmpVec3.x >= abstmpVec3.y && abstmpVec3.x >= abstmpVec3.z)
    {
        if(tmpVec3.x < 0)
            realTexCoord.x = tmpVec3.z/abstmpVec3.x;
        else
        	realTexCoord.x = -tmpVec3.z/abstmpVec3.x;
        realTexCoord.y = tmpVec3.y/abstmpVec3.x;
        realTexCoord=(realTexCoord+vec2(1))/2;
	    if(tmpVec3.x>0)
	    	FragColor=texture(right,realTexCoord);
	    else
	    	FragColor=texture(left,realTexCoord);

	}
	if (abstmpVec3.y >= abstmpVec3.x && abstmpVec3.y >= abstmpVec3.z)
	{
	    if(tmpVec3.y < 0)
			realTexCoord.x = tmpVec3.x/abstmpVec3.y;
	    else
	    	realTexCoord.x = -tmpVec3.x/abstmpVec3.y;
	    realTexCoord.y = tmpVec3.z/abstmpVec3.y;
	    realTexCoord=(realTexCoord+vec2(1))/2;
	    if(tmpVec3.y>0)
	    	FragColor=texture(top,realTexCoord);
	    else
	    	FragColor=texture(bottom,realTexCoord);
	}
	if (abstmpVec3.z >= abstmpVec3.y && abstmpVec3.z >= abstmpVec3.x)
	{
	    if(tmpVec3.z < 0) 
			realTexCoord.x = -tmpVec3.x/abstmpVec3.z;
	    else
	    	realTexCoord.x = tmpVec3.x/abstmpVec3.z;
	    realTexCoord.y = tmpVec3.y/abstmpVec3.z;
	    realTexCoord=(realTexCoord+vec2(1))/2;
	    if(tmpVec3.z>0)
	    	FragColor=texture(front,realTexCoord);
	    else
	    	FragColor=texture(back,realTexCoord);
	}

	
}