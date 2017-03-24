#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

// just sample the target and return the colour
vec4 Simple() {
	return texture(target, fTexCoord);
}

vec4 Implosion () {
	vec2 center = vec2(0.5,0.5) - fTexCoord;
	vec2 mcenter = 0.07*log(length(center))*normalize(center);
	
	return texture(target, fTexCoord+mcenter);
}

vec4 Explosion () {
	vec2 center = vec2(0.5,0.5) - fTexCoord;
	vec2 mcenter = -0.07*log(length(center))*normalize(center);
	
	return texture(target, fTexCoord+mcenter);
}

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

float rand(vec2 co)
{
	return fract(sin(dot(co.xy ,vec2(92.,80.))) + cos(dot(co.xy ,vec2(41.,62.))) * 5.1);
}

vec4 Fuzz()
{
	vec2 rnd = vec2(rand(fTexCoord),rand(fTexCoord));
	return texture(target, fTexCoord+rnd*0.005);
}



vec4 Fog() {
	
	float FogDensity = 10.0;
	vec4 FogColour = vec4(0.25,0.25,0.25,1.0);
	vec4 CurrentColour = texture2D(target,fTexCoord);
	
	// distance to target
	float FogDistance = distance(vec2(0.49,0.46),fTexCoord);
	
	float FogFactor = exp(-abs(FogDistance * FogDensity));
	
	return mix(FogColour,CurrentColour,FogFactor);
}

vec4 BoxBlur() {
vec2 texel = 1.0f / textureSize(target, 0).xy;
// 9-tap box kernel
vec4 colour = texture(target, fTexCoord);
colour += texture(target, fTexCoord + vec2(-texel.x, texel.y));
colour += texture(target, fTexCoord + vec2(-texel.x, 0));
colour += texture(target, fTexCoord + vec2(-texel.x, -texel.y));
colour += texture(target, fTexCoord + vec2(0, texel.y));
colour += texture(target, fTexCoord + vec2(0, -texel.y));
colour += texture(target, fTexCoord + vec2(texel.x, texel.y));
colour += texture(target, fTexCoord + vec2(texel.x, 0));
	colour += texture(target, fTexCoord + vec2(texel.x, -texel.y));
	return colour / 9;
}

vec4 Distort() {
vec2 mid = vec2(0.5f);
float distanceFromCentre = distance(fTexCoord, mid);
vec2 normalizedCoord = normalize(fTexCoord - mid);
float bias = distanceFromCentre +
sin(distanceFromCentre * 15) * 0.02f;
vec2 newCoord = mid + bias * normalizedCoord;
return texture(target, newCoord);
}

void main() {
//fragColour = BoxBlur();
//fragColour = Distort();
//fragColour = Simple();
fragColour = Fog();
//fragColour = Implosion();
//fragColour = Thermal();
//fragColour = Fuzz();
}