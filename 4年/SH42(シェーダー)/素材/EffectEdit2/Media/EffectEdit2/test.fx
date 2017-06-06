string XFile = "misc/nanase_pose.x";
int BCLR = 0x000000ff;

// 変換マトリックス
float4x4 matWVP : WORLDVIEWPROJECTION;  // ワールド×ビュー×射影
//                ^^^^^^^^^^^^^^^^^^^ セマンティクス (ユーザ定義)
float4x4 matW   : WORLD;                // ワールド

float3 camera   : CAMERAPOSITION;       //視点座標

// 光源ベクトル (光の進む方向)
float3 light
  <string UIDirectional = "Light Direction";>
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ アノテーション
= {-0.35f, -0.25f, 0.9f};

// 光源の色
float4  I_d = {1.0f, 1.0f, 1.0f, 1.0f};//拡散光
float4  I_a = {0.2f, 0.2f, 0.2f, 1.0f};//環境光
float4  I_s = {1.0f, 1.0f, 1.0f, 1.0f};//鏡面反射光

// Xファイル　マテリアル
float4  k_d : MATERIALDIFFUSE;   //拡散色
float4  k_s : MATERIALSPECULAR;  //鏡面反射色
float   k_p : MATERIALPOWER;     //鏡面反射指数
float4  k_a : MATERIALAMBIENT;   //環境色
texture tex : MATERIALTEXTURE;
bool    tex_enable : MATERIALTEXTUREVALID;

// サンプラステート
sampler Sampler = sampler_state
{
    Texture = (tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// 頂点シェーダ
void testVS(float3 InPos : POSITION,
//                         ^^^^^^^^ セマンティクス(システム定義)
            float3 InNor : NORMAL,
            float2 InTex : TEXCOORD0,
            out float4 OutPos  : POSITION,
            out float4 OutDiff : COLOR0,
            out float4 OutSpec : COLOR1,
            out float2 OutTex  : TEXCOORD0)
{
    OutPos = mul(float4(InPos, 1), matWVP);
    float3 L = normalize(-light);
    float3 N = mul(InNor, (float3x3)matW);
    float3 P = mul(float4(InPos, 1), matW).xyz;
    float3 V = normalize(camera - P);
    float3 R = reflect(-V, N);
    OutDiff = I_a * k_a + I_d * k_d * saturate(dot(L, N));
    OutSpec = I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
    OutTex = InTex;
}

// ピクセルシェーダ
void testPS(float4 InDiff : COLOR0,
            float4 InSpec : COLOR1,
            float2 InTex  : TEXCOORD0,
            out float4 OutCol : COLOR0)
{
    OutCol = InDiff;
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    OutCol += InSpec;
}

// テクニック
technique tec0
{
    // パス
    pass p0
    {
        VertexShader = compile vs_2_0 testVS();
        PixelShader = compile ps_2_0 testPS();
    }
}