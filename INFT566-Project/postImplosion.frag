#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

vec4 Implosion () {
	vec2 center = vec2(0.5,0.5) - fTexCoord;
	vec2 mcenter = 0.07*log(length(center))*normalize(center);
	
	return texture(target, fTexCoord+mcenter);
}

void main()
{
	fragColour = Implosion();
}