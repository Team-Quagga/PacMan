#version 330

in vec3 inputPosition;
in vec3 inputColor;
varying vec2 texCoord;
in vec3 inputNormal;
in vec3 diffuseColor;

vec3 LightPos = vec3(5, 3, 5);

out vec3 color;
out vec2 texcoord;
out vec3 normal;
out vec3 light;
out vec3 vertex;
out vec3 diffuse;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(inputPosition, 1.0);

	color = inputColor;
	texcoord = texCoord;
	normal = inputNormal;
	light = LightPos;
	vertex = inputPosition;
	diffuse = diffuseColor;
}