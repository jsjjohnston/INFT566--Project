#version 430

in vec3 theNormal;
in vec3 thePosition;

uniform vec3 lightPosition;

out vec4 FragColor;

void main() {

	vec3 lightVector = normalize(lightPosition - thePosition);
	float brightness = dot(lightVector,theNormal);
	FragColor = vec4(brightness,brightness,brightness,1.0);
}