#version 330 core

layout(location = 0) in vec3 l_Position;

uniform float u_X;
uniform float u_Y;

out vec2 a_UvTex;

void main()
{
    gl_Position = vec4(l_Position.x + u_X, l_Position.y + u_Y, l_Position.z, 1);
	a_UvTex = (l_Position.xy + vec2(1, 1)) / 2.0;
}

