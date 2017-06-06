// バンプマッピング (EffectEdit2用)
//
string XFile = "misc/teapot2.x";
//string XFile = "Bump/square.x";

float3 lightDir
<
    string UIDirectional = "Light Direction";
> = {-0.35f, -0.25f, 0.9f};

float3 CameraPos : CAMERAPOSITION;

float4 I_a = {0.1f, 0.1f, 0.1f, 1.0f};
float4 I_d = {1.0f, 1.0f, 1.0f, 1.0f};
float4 I_s = {1.0f, 1.0f, 1.0f, 1.0f};

float4  k_a : MATERIALAMBIENT;
float4  k_d : MATERIALDIFFUSE;
float4  k_s : MATERIALSPECULAR;
float   k_n : MATERIALPOWER;
texture k_t : MATERIALTEXTURE;      // 使用しない
bool    k_e : MATERIALTEXTUREVAID;  // 使用しない

// バンプマップ用テクスチャ
texture Tex < string Name = "Earth/earth.bmp"; >;               // 通常テクスチャ
//texture Tex < string Name = "Bump/stones.bmp"; >;               // 通常テクスチャ
texture NormalMap < string Name = "Earth/earthnormal.bmp"; >;   // 法線マップ テクスチャ
//texture NormalMap < string Name = "Bump/stones_NM_height.tga"; >;   // 法線マップ テクスチャ

// 変換マトリックス
float4x4 World : WORLD;
float4x4 WorldViewProj : WORLDVIEWPROJECTION;

sampler Sampler = sampler_state     // 使用しない
{
    Texture = (k_t);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler TexSampler = sampler_state
{
    Texture = (Tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler NormalSampler = sampler_state
{
    Texture = (NormalMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// バンプマッピング (頂点シェーダ)
void BumpMapVS(float3 InPos  : POSITION,
               float3 InTan  : TANGENT,
               float3 InNorm : NORMAL,
               float2 InTex  : TEXCOORD0,
               out float4 OutPos   : POSITION,
               out float2 OutTex   : TEXCOORD0,
               out float3 OutLight : TEXCOORD1,
               out float3 OutView  : TEXCOORD2)
{
    OutPos = mul(float4(InPos, 1), WorldViewProj);          // 頂点座標 (射影空間)
    OutTex = InTex;                                         // テクスチャ座標
    float3 BiNormal = cross(InNorm, InTan);                 // 従法線を求める
    float4 P = mul(float4(InPos, 1), World);                // 頂点座標 (ワールド空間)
    float3 T = normalize(mul(InTan, (float3x3)World));      // 接ベクトル (ワールド空間)
    float3 B = normalize(mul(BiNormal, (float3x3)World));   // 従法線ベクトル (ワールド空間)
    float3 N = normalize(mul(InNorm, (float3x3)World));     // 法線ベクトル (ワールド空間)
    float3 V = normalize(CameraPos - P);                    // 視点へのベクトル (ワールド空間)
    float3 L = normalize(-lightDir);                        // 光源へのベクトル (ワールド空間)
    OutView.x = dot(V, B);                                  // 視点へのベクトル (接空間)
    OutView.y = dot(V, T);
    OutView.z = dot(V, N);
    OutLight.x = dot(L, B);                                 // 光源へのベクトル (接空間)
    OutLight.y = dot(L, T);
    OutLight.z = dot(L, N);
}

// バンプマッピング (ピクセルシェーダ)
void BumpMapPS(float2 InTex   : TEXCOORD0,
               float3 InLight : TEXCOORD1,
               float3 InView  : TEXCOORD2,
               out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);                          // 光源へのベクトル (接空間)
    float3 N = tex2D(NormalSampler, InTex) * 2.0f - 1.0f;   // 法線ベクトル (接空間)
    N = normalize(float3(-N.y, -N.x, N.z));
    float3 V = normalize(InView);                           // 視点へのベクトル (接空間)
    float3 R = reflect(-V, N);                              // 反射ベクトル (接空間)
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // 拡散光
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // 鏡面反射光
    OutCol = tex2D(TexSampler, InTex) * Diff + Spec;        // 最終的な色
}

// バンプマッピング
technique TBumpMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpMapVS();
        PixelShader  = compile ps_3_0 BumpMapPS();
    }
}
