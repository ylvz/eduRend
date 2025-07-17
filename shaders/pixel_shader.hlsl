Texture2D texDiffuse : register(t0);
SamplerState texSampler : register(s0);

cbuffer LightBuffer : register(b0)
{
    float4 lightPos;
    float4 camPos;
};

cbuffer MaterialBuffer : register(b1)
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float shininess;
    float3 padding;
};

struct PSIn
{
    float4 Pos : SV_Position;
    float3 Normal : NORMAL;
    float2 TexCoord : TEX;
    float3 PosWorld : WORLD;
};

float4 PS_main(PSIn input) : SV_Target
{
    float3 N = normalize(input.Normal);
    float3 L = normalize(lightPos.xyz - input.PosWorld);
    float3 V = normalize(camPos.xyz - input.PosWorld);
    float3 R = reflect(-L, N);

    float3 ambientTerm = ambient.xyz;

    float diff = max(dot(L, N), 0.0f);
    float4 texColor = texDiffuse.Sample(texSampler, input.TexCoord); // SAMPLE TEXTURE
    float3 diffuseTerm = texColor.rgb * diff;

    float spec = pow(max(dot(R, V), 0.0f), shininess);
    float3 specularTerm = specular.xyz * spec;

    float3 finalColor = ambientTerm + diffuseTerm + specularTerm;

    return float4(finalColor, 1.0f);
}
