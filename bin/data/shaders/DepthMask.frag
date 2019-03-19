#version 330 core

in vec2 a_UvTex;

uniform mat4 u_ProjectionMatrix;
uniform sampler2D u_TextureSampler;
uniform float u_ZNear;
uniform float u_ZFar;

void main() 
{
   float imageDepth = texture(u_TextureSampler, a_UvTex).r;
   imageDepth = -imageDepth;
   vec4 temp = vec4(0.0, 0.0, (imageDepth * (u_ZFar - u_ZNear) - u_ZNear), 1.0);
   vec4 clipSpace = u_ProjectionMatrix * temp;
   clipSpace.z /= clipSpace.w;
   clipSpace.z = 0.5 * (clipSpace.z + 1.0);
   float depth = clipSpace.z;
   gl_FragDepth = depth;
   // float linearDepth = texture(u_TextureSampler, a_UvTex).r;
   // gl_FragDepth = -((u_ZNear + u_ZFar) * linearDepth - (2.0 * u_ZNear)) / ((u_ZNear - u_ZFar) * linearDepth);
}

