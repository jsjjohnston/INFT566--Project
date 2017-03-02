#version 430

layout (location=0) in vec3 VertexPosition;

out vec3 Color;

uniform mat4 projectionViewWorldMatrix;

void main()
{
	Color = vec3(1,0,1);
	gl_Position = projectionViewWorldMatrix * vec4(VertexPosition,1.0);
}