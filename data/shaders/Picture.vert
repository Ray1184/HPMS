#version 330 core

layout(location = 0) in vec3 position;

//uniform float x;
//uniform float y;

//out vec2 uvTex;

void main()
{
    gl_Position = vec4(position.x + x, position.y + y, position.z, 1);
	//uvTex = (position.xy + vec2(1, 1)) / 2.0;
}

