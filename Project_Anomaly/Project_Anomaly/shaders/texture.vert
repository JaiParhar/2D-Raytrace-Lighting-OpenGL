#version 460 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPos_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main()
{
	gl_Position.xyz = vertexPos_modelspace;
	gl_Position.w = 1.0;

	UV = vertexUV;
}