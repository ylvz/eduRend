
Texture2D texDiffuse : register(t0);

cbuffer LightCamBuffer : register(b0)
{
    float4 LightPosition;
    float4 CameraPosition;
};

cbuffer MaterialBuffer : register(b1)
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float shininess;
};

struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float2 TexCoord : TEX;
    float3 PosWorld : WORLD;
};

//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{
    float3 N = normalize(input.Normal);
    float3 L = normalize(LightPosition.xyz - input.PosWorld.xyz); // Light direction
    float3 V = normalize(CameraPosition.xyz - input.PosWorld.xyz); // View direction (FIXED)
    float3 R = reflect(-L, N); // Reflection vector

// Diffuse (Lambert)
    float lambert_diffuse = max(dot(N, L), 0.0);

// Specular (Phong)
    float specular_highlight = pow(max(dot(R, V), 0.0), shininess); // Removed abs()

// Combine components
    float3 ambient_component = ambient.rgb;
    float3 diffuse_component = diffuse.rgb * lambert_diffuse;
    float3 specular_component = specular.rgb * specular_highlight;

// Final color (ensure it's red if testing)
    float3 phong_illumination = ambient_component + diffuse_component + specular_component;
    return float4(phong_illumination, 1.0);

}


