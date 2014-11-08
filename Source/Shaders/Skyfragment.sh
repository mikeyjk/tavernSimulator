#version 330

in vec3 texCoord;
out vec4 fragColor;
uniform samplerCube textureMap;

void main (void) 
{
	fragColor = texture(textureMap, texCoord);
}