#version 460 core

layout (location = 0) in vec3 inColor;
layout (location = 0) out vec4 outColor;


void main()
{
	outColor = vec4(1, 1, 1, 1);
	outColor.rgb = inColor;
}