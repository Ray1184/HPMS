#version 330 core

in vec2 a_TexCoord;
in vec3 a_VertNormal;
out vec4 a_Color;


struct Material
{
    vec4 diffuse;
    int hasTexture;
};

uniform sampler2D u_TextureSampler;
uniform vec3 u_AmbientLight;
uniform Material u_Material;
uniform float u_DiffuseIntensity;

vec4 diffuseC;
vec4 diffuseK;

void SetupColours(Material material, vec2 textCoord)
{
    if (material.hasTexture == 1)
    {
        diffuseC = texture(u_TextureSampler, textCoord);
    }
    else
    {
        diffuseC = material.diffuse;
    }

    vec3 lightDirection = vec3(0, 0, 1);
    vec3 source = normalize(lightDirection);
    float diffuseFactor = max(dot(a_VertNormal, source), 0.0);
    diffuseK = diffuseC * diffuseFactor * u_DiffuseIntensity;
}



void main()
{
    SetupColours(u_Material, a_TexCoord);
    a_Color = clamp(diffuseC * vec4(u_AmbientLight, 1), 0, 1) + diffuseK;
}