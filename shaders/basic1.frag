#version 450 core

layout(location=0) in vec3 vClrCoord;

layout (location=0) out vec4 fFragClr;

void main () {
  fFragClr = vec4(1,1,1, 1);
}
