#version 430

in vec3 normalWorld; // Normalised surface normal from mesh
in vec3 vertexPositionWorld; // World-space surface position from mesh
in vec2 vTexCoord;

uniform vec3 eyePositionWorld; // World-space Camera Position
uniform vec3 lightPositionWorld; // Normalised Light direction
uniform vec4 ambientLight;

uniform sampler2D diffuseTex;

out vec4 FragColor;

void main()
{
	// diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuse = texture(diffuseTex,vTexCoord);
	vec4 diffuseLight = vec4(diffuse.r * brightness, diffuse.g * brightness, diffuse.b * brightness, 1.0);
	
	// Specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld), 0, 1);
	s = pow(s, 50);
	vec4 specularLight = vec4(s, 0, 0, 1);
	
	//FragColor = texture(diffuseTex,vTexCoord) * vec4(Ambient+Diffuse+Specular,1);
	FragColor = ambientLight + clamp(diffuseLight, 0, 1) + specularLight;
}