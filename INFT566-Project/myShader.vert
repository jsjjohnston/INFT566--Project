#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 normal;

out vec3 Color;

uniform mat4 fullFransform;
uniform vec3 ambientLight;

void main()
{
	//Color = vec3(0,0,1.0) * ambientLight;
	Color = normal;
	gl_Position = fullFransform * vec4(VertexPosition, 1.0);
}