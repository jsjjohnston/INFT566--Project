#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

vec4 Distort() {
	vec2 mid = vec2(0.5f);
	float distanceFromCentre = distance(fTexCoord, mid);
	vec2 normalizedCoord = normalize(fTexCoord - mid);
	float bias = distanceFromCentre +
	sin(distanceFromCentre * 15) * 0.02f;
	vec2 newCoord = mid + bias * normalizedCoord;
	return texture(target, newCoord);
}

void main()
{
	fragColour = Distort();
}