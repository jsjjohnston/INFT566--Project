#version 410

in vec2 fTexCoord;

out vec4 fragColour;

uniform sampler2D target;

void main()
{
	vec4 sum = vec4(0);
		
	int j;
	int i;
	
	for(i = -4; i < 4; i++)
	{
		for(j = -3; j < 3; j++)
		{
			sum += texture(target, fTexCoord + vec2(j, i)*0.04) + 0.25;
		}
	}
	
	if( texture(target,fTexCoord).r < 0.3)
	{
		fragColour = sum*0.012 + texture(target,fTexCoord);
	} 
	else
	{
		if (texture(target,fTexCoord).r < 0.5)
        {
			fragColour = sum*0.009 + texture(target,fTexCoord);
        }
        else
        {
			fragColour = sum*0.0075 + texture(target,fTexCoord);
        }
	}
}