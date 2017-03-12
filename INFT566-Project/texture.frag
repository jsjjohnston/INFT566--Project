#version 430

in vec3 normalWorld;
in vec3 vertexPositionWorld;
in vec2 vTexCoord;

uniform vec3 lightPositionWorld;
uniform vec4 ambientLight;
uniform vec3 eyePositionWorld;
uniform sampler2D diffuse;

out vec4 FragColor;

void main() {
	// Diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld,normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness,brightness,brightness,1.0);
	
	// Specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = dot(reflectedLightVectorWorld, eyeVectorWorld);
	s = pow(s,32);
	vec4 specularLight = vec4(0,0,s,1);
	FragColor = ambientLight+ clamp(diffuseLight,0,1) + clamp(specularLight,0,1);
	//FragColor = texture(diffuse,vTexCoord);
}