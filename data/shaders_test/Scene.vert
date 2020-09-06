#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	mat4 mvp = projMatrix * viewMatrix * modelMatrix;
	gl_Position = mvp * vec4(vertexPosition_modelspace, 1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vec3(1, 0, 0);
}
