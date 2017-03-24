#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

void main()
{
	mat3 sx = mat3( 
		1.0, 2.0, 1.0, 
		0.0, 0.0, 0.0, 
		-1.0, -2.0, -1.0 
	);
	mat3 sy = mat3( 
		1.0, 0.0, -1.0, 
		2.0, 0.0, -2.0, 
		1.0, 0.0, -1.0 
	);

	vec3 diffuse = texture(target, fTexCoord).rgb;
	mat3 I;
	
	for (int i=0; i<3; i++) {
       for (int j=0; j<3; j++) {
            vec3 a  = texelFetch(target, ivec2(gl_FragCoord) + ivec2(i-1,j-1), 0 ).rgb;
            I[i][j] = length(a); 
    }}

	float gx = dot(sx[0], I[0]) + dot(sx[1], I[1]) + dot(sx[2], I[2]); 
	float gy = dot(sy[0], I[0]) + dot(sy[1], I[1]) + dot(sy[2], I[2]);

	float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));
	g = smoothstep(0.1, 0.6, g);

    vec3 edgeColor = vec3(0.0, 0.0, 1.0);
	fragColour = vec4(mix(diffuse, edgeColor, g), 1.0);
}


