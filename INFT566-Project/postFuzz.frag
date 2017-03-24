#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

float rand(vec2 co)
{
	return fract(sin(dot(co.xy ,vec2(92.,80.))) + cos(dot(co.xy ,vec2(41.,62.))) * 5.1);
}

vec4 Fuzz()
{
	vec2 rnd = vec2(rand(fTexCoord),rand(fTexCoord));
	return texture(target, fTexCoord+rnd*0.005);
}

void main()
{
	fragColour = Fuzz();
}