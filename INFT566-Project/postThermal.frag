#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

vec4 Thermal()
{
	vec4 pixelColour = texture(target, fTexCoord);
	vec4 colours[3];
	colours[0] = vec4(0.0,0.0,1.0,1.0);
	colours[1] = vec4(1.0,1.0,0.0,1.0);
	colours[2] = vec4(1.0,0.0,0.0,1.0);
	
	float lum = (pixelColour.r+pixelColour.g+pixelColour.b) /3;
	int ix = (lum < 0.5f)? 0:1;
	
	return mix(colours[ix],colours[ix+1],(lum-float(ix)*0.5)/0.5);
}

void main()
{
	fragColour = Thermal();
}