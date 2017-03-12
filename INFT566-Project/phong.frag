#version 430

uniform vec3 kA = vec3(1,0,0); // Red Ambient Material Colour
uniform vec3 kD = vec3(0,1,0); // Red Diffuse Material Colour
uniform vec3 kS = vec3(0,0,1); // Red Specular Material Colour

uniform vec3 iA = vec3(0.25f,0.25f,0.25f);
uniform vec3 iD = vec3(1,1,1);
uniform vec3 iS = vec3(1,1,1);
uniform float iSpecPower = 32.0f; // Specular Power

in vec3 normalWorld; // Normalised surface normal from mesh
in vec3 vertexPositionWorld; // World-space surface position from mesh

uniform vec3 camPos; // World-space Camera Position
uniform vec3 L; // Normalised Light direction

out vec4 FragColor;

void main()
{
	vec3 Ambient = kA * iA; // Set Ambient Light
	
	float Ndl = max(0.0f, dot(normalWorld, -L)); //Lambert term
	vec3 Diffuse = kD *iD * Ndl; // Diffuse Light for one Light
	
	vec3 R = reflect(L, normalWorld);
	vec3 E = normalize(camPos - vertexPositionWorld);
	
	float specTerm = pow(min(0.0f, dot(R,E)),iSpecPower);
	vec3 Specular = kS * iS * specTerm;
	FragColor = vec4(Ambient+Diffuse+Specular,1);
}