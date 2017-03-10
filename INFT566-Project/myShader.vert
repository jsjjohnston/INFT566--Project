#version 430

layout (location=0) in vec3 VertexPositionModel;
layout (location=1) in vec3 normalModel;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldTransformMatrix;

out vec3 normalWorld;
out vec3 vertexPositionWorld;

void main()
{
	gl_Position = modelToProjectionMatrix * vec4(VertexPositionModel, 1.0);
	normalWorld = vec3(modelToWorldTransformMatrix * vec4(normalModel,0));
	vertexPositionWorld = vec3(modelToWorldTransformMatrix * vec4(VertexPositionModel, 1.0));	
}