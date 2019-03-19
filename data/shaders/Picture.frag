#version 330 core

in vec2 a_UvTex;

out vec4 a_Color;

uniform sampler2D u_TextureSampler;
uniform float u_Alpha;

void main()
{
	vec4 tempColor = texture(u_TextureSampler, a_UvTex);
	a_Color = vec4(tempColor.x, tempColor.y, tempColor.z, tempColor.w * u_Alpha);
}