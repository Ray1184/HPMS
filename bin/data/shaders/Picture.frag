#version 330 core

in vec2 uvTex;

out vec4 color;

uniform sampler2D textureSampler;
uniform float alpha;

void main()
{
	vec4 tempColor = texture(textureSampler, uvTex);
	color = vec4(tempColor.x, tempColor.y, tempColor.z, tempColor.w * alpha);
	//color = vec4(1, 0, 1, 1);
}