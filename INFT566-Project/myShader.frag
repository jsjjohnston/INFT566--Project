#version 430

in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;

out vec4 FragColor;

void main() {

	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld,normalize(normalWorld));
	FragColor = vec4(brightness,brightness,brightness,1.0);
}