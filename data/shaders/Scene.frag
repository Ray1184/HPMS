#version 330 core

in vec2 outTexCoord;
in vec3 outVertNormal;
out vec4 fragColor;


struct Material
{
    vec4 diffuse;
    int hasTexture;
};

uniform sampler2D textureSampler;
uniform vec3 ambientLight;
uniform Material material;
uniform float diffuseIntensity;

vec4 diffuseC;
vec4 diffuseK;

void setupColours(Material material, vec2 textCoord)
{
    if (material.hasTexture == 1)
    {
        diffuseC = texture(textureSampler, textCoord);
    }
    else
    {
        diffuseC = material.diffuse;
    }

    vec3 lightDirection = vec3(0, 0, 1);
    vec3 source = normalize(lightDirection);
    float diffuseFactor = max(dot(outVertNormal, source), 0.0);
    diffuseK = diffuseC * diffuseFactor * diffuseIntensity;
}



void main()
{
    setupColours(material, outTexCoord);
    fragColor = clamp(diffuseC * vec4(ambientLight, 1), 0, 1) + diffuseK;
}