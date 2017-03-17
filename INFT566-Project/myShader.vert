#version 430

layout (location=0) in vec3 VertexPositionModel;
layout (location=1) in vec3 normalModel;
layout (location=2) in vec2 texCoord;

layout (location=3) in vec4 quadPosition;
layout (location=4) in vec2 quadTexCoord;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldTransformMatrix;

out vec3 normalWorld;
out vec3 vertexPositionWorld;
out vec2 vTexCoord;

out vec2 fquadTexCoord;

void main()
{
	fquadTexCoord = quadTexCoord;

	vTexCoord = texCoord;
	//gl_Position = modelToProjectionMatrix * vec4(VertexPositionModel, 1.0) * quadPosition;
	gl_Position = modelToProjectionMatrix * vec4(VertexPositionModel, 1.0);
	normalWorld = vec3(modelToWorldTransformMatrix * vec4(normalModel,0));
	vertexPositionWorld = vec3(modelToWorldTransformMatrix * vec4(VertexPositionModel, 1.0));	
	
	//gl_Position = quadPosition;
}