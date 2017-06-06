// VolumeTex.fx

//string XFile = "Airplane/airplane 2.x"; // model
string XFile = "misc/teapot2.x";        // model

// light direction (view space)
float3 lightDir < string UIDirectional = "Light Direction"; > = {0.577, -0.577, 0.577};

// light parameter
float4 LightDiffuseColor        = { 1.0f, 0.9f, 0.8f, 1.0f };    // diffuse
float4 LightSpecularColor       = { 1.0f, 1.0f, 1.0f, 1.0f };    // specular

// material
float4 MaterialDiffuseColor     = { 0.4f, 0.4f, 0.4f, 1.0f };    // diffuse
float4 MaterialSpecularColor    = { 0.2f, 0.2f, 0.2f, 1.0f };    // specular
float  MaterialSpecularPower    = 32;                            // power

// matrix
float4x4 WorldView  : WORLDVIEW;
float4x4 Projection : PROJECTION;

// camera position
float3 CameraPos : CAMERAPOSITION;

// timer
float Time : TIME;

// volume texture (external)
texture VolTex1 < string type = "VOLUME"; string name = "misc/VolTexShine.dds"; >;

// volume map
texture VolumeMap 
< 
    string type = "VOLUME"; 
    string function = "GenerateVolumeMap"; 
    int width  = 32;
    int height = 32;
    int depth  = 32;
>;

// generate volume map
float4 GenerateVolumeMap(float3 Pos : POSITION) : COLOR
{
    return noise(Pos * 10.0) * 3.0;
}

// sampler
sampler3D VolumeTexture =
sampler_state
{
//    texture = (VolumeMap);
    texture = (VolTex1);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// vertex shader
void VolumeTex_vs_main(float3 InPos    : POSITION,
                       float3 InNormal : NORMAL,
                       float2 InTex    : TEXCOORD0,
                       out float4 OutPos  : POSITION,
                       out float4 OutDiff : COLOR0,
                       out float4 OutSpec : COLOR1,
                       out float2 OutTex  : TEXCOORD2,
                       out float3 VolTex  : TEXCOORD1)
{
    float3 P = mul(float4(InPos, 1), WorldView);

    float3 N = normalize(mul(InNormal, WorldView));
    float3 V = normalize(P - CameraPos);

    OutPos  = mul(float4(P, 1), Projection);
 
    OutDiff = MaterialDiffuseColor * LightDiffuseColor * max(0, dot(N, -lightDir));
    float3 R = normalize(reflect(lightDir, N));
    OutSpec = MaterialSpecularColor * LightSpecularColor 
            * pow(max(0, dot(R, -V)), MaterialSpecularPower/4);

    VolTex = InPos * 4.0;
//    VolTex.x = VolTex.x + Time * 0.25;
//    VolTex.y = VolTex.y + Time * 0.25;
    VolTex.z = VolTex.z + Time * 0.25;

    OutTex = InTex;
}

// pixel shader
void VolumeTex_ps_main(float4 Diff   : COLOR0,
                       float4 Spec   : COLOR1,
                       float3 VolTex : TEXCOORD1,
                       out float4 Col0 : COLOR)
{
    Col0 = Diff;
    Col0 += tex3D(VolumeTexture, VolTex);
    Col0 += Spec;
}

// technique
technique VolumeTex
{
    pass P0
    {
        VertexShader = compile vs_2_0 VolumeTex_vs_main();
        PixelShader  = compile ps_2_0 VolumeTex_ps_main();
    }
}
