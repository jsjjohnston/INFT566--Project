#version 430

layout (location=0) in vec3 VertexPositionModel;
layout (location=1) in vec3 normalModel;

uniform mat4 fullFransform;
uniform mat4 modelToWorldTransformMatrix;

out vec3 theNormal;
out vec3 thePosition;

void main()
{
	gl_Position = fullFransform * vec4(VertexPositionModel, 1.0);
	theNormal = vec3(modelToWorldTransformMatrix * vec4(normalModel,0));
	thePosition = vec3(modelToWorldTransformMatrix * vec4(VertexPositionModel, 1.0));	
}