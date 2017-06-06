//
// Hemisphere Lighting Model
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// 注意：このエフェクトファイルはEffectEditに対応するものです。
//
string XFile = "misc/SkullOcc.x";   // モデル
int BCLR = 0xff202080;              // 背景

// 光の方向(ビュー空間)
float3 DirFromLight < string UIDirectional = "Light Direction"; > =
    {0.577, -0.577, 0.577};

// 空からの光の方向(ビュー空間)
float3 DirFromSky < string UIDirectional = "Direction from Sky"; > =
    { 0.0f, -1.0f, 0.0f };

// 光の強度
float4 I_a = { 0.5f, 0.5f, 0.5f, 1.0f }; // ambient
float4 I_b = { 0.1f, 0.0f, 0.0f, 1.0f }; // ground
float4 I_c = { 0.9f, 0.9f, 1.0f, 1.0f }; // sky
float4 I_d = { 1.0f, 0.9f, 0.8f, 1.0f }; // diffuse
float4 I_s = { 1.0f, 1.0f, 1.0f, 1.0f }; // specular

// material reflectivity
float4 k_a = { 0.8f, 0.8f, 0.8f, 1.0f }; // ambient
float4 k_d = { 0.4f, 0.4f, 0.4f, 1.0f }; // diffuse
float4 k_s = { 0.1f, 0.1f, 0.1f, 1.0f }; // specular
int n = 32; // power

// transformations
float4x3 WorldView : WORLDVIEW;
float4x4 Projection : PROJECTION;

struct VS_OUTPUT
{
    float4 Pos : POSITION;
    float4 Diff : COLOR0;
    float4 Spec : COLOR1;
};
VS_OUTPUT VS(
    float3 Pos : POSITION,
    float3 Norm : NORMAL,
    float Occ : TEXCOORD0,
    uniform bool bHemi,
    uniform bool bDiff,
    uniform bool bSpec)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;
    // diffuse direction
    float3 L = -DirFromLight;
    // hemisphere up axis
    float3 Y = -DirFromSky;
    // position (view space)
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);
    // normal (view space)
    float3 N = normalize(mul(Norm, (float3x3)WorldView));
    // reflection vector (view space)
    float3 R = normalize(2 * dot(N, L) * N - L);
    // view direction (view space)
    float3 V = -normalize(P);
    float4 Amb = k_a * I_a;
    float4 Hemi = k_a * lerp(I_b, I_c, (dot(N, Y) + 1) / 2) * (1 - Occ);
    float temp = 1 - max(0, dot(N, L));
    float4 Diff = k_d * I_d * (1 - temp * temp);
    float4 Spec = k_s * I_s * pow(max(0, dot(R, V)), n/4);
    float4 Zero = 0;

    // position (projected)
    Out.Pos = mul(float4(P, 1), Projection);

    // diffuse + ambient/hemisphere
    Out.Diff = (bDiff ? Diff : 0)
        + (bHemi ? Hemi : Amb);

    // specular
    Out.Spec = (bSpec ? Spec : 0);

    return Out;
}

technique THemisphere
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS(true, false, false);
    }
}

technique THemisphereDiffuse
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS(true, true, false);
    }
}

technique THemisphereDiffuseSpecular
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS(true, true, true);
        SpecularEnable = TRUE;
    }
}

technique TAmbient
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS(false, false, false);
    }
}

technique TAmbientDiffuse
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS(false, true, false);
    }
}

technique TAmbientDiffuseSpecular
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS(false, true, true);
        SpecularEnable = TRUE;
    }
}
