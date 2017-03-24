#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

vec4 Fog() {
	
	float FogDensity = 10.0;
	vec4 FogColour = vec4(0.25,0.25,0.25,1.0);
	vec4 CurrentColour = texture2D(target,fTexCoord);
	
	// distance to target
	float FogDistance = distance(vec2(0.49,0.46),fTexCoord);
	
	float FogFactor = exp(-abs(FogDistance * FogDensity));
	
	return mix(FogColour,CurrentColour,FogFactor);
}

void main()
{
	fragColour = Fog();
}