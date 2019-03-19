#version 330 core

const int MAX_WEIGHTS = 4;
const int MAX_JOINTS = 150;

layout (location=0) in vec3 l_Position;
layout (location=1) in vec2 l_TexCoord;
layout (location=2) in vec3 l_VertexNormal;
layout (location=3) in vec4 l_JointWeights;
layout (location=4) in ivec4 l_JointIndices;

out vec2 a_TexCoord;
out vec3 a_VertNormal;


uniform mat4 u_JointsMatrix[MAX_JOINTS];
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelViewMatrix;

void main()
{

    vec4 initPos = vec4(0, 0, 0, 0);
    vec4 initNormal = vec4(0, 0, 0, 0);

    int count = 0;
    for (int i = 0; i < MAX_WEIGHTS; i++)
    {
        float weight = l_JointWeights[i];
        if (weight > 0) {
            count++;
            int jointIndex = l_JointIndices[i];
            vec4 tmpPos = u_JointsMatrix[jointIndex] * vec4(l_Position, 1.0);
            initPos += weight * tmpPos;
        }
    }
    if (count == 0)
    {
        initPos = vec4(l_Position, 1.0);
    }

    vec4 mvPos = u_ModelViewMatrix * initPos;
    gl_Position = u_ProjectionMatrix * mvPos;

    a_VertNormal = normalize(u_ModelViewMatrix * vec4(l_VertexNormal, 0.0)).xyz;
    a_TexCoord = l_TexCoord;


}