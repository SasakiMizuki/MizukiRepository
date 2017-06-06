// 各種ライティング
//
//string XFile = "misc/nanase_pose.x";float weight = 0.003f;
//string XFile = "misc/mone_pose.x";float weight = 0.003f;
//string XFile = "misc/maid_pose.x";float weight = 0.005f;
//string XFile = "fig01/fig01.x";float weight = 0.001f;
string XFile = "hackadoll/1号_v1.00.x";float weight = 0.2f;
//string XFile = "hackadoll/2号_v1.00.x";float weight = 0.2f;
//string XFile = "hackadoll/3号_v1.00.x";float weight = 0.2f;

int BCLR = 0x000000ff;

// 変換マトリックス
float4x4 matWVP : WORLDVIEWPROJECTION;  // ワールド×ビュー×射影
//                ^^^^^^^^^^^^^^^^^^^ セマンティクス (ユーザ定義)
float4x4 matW   : WORLD;                // ワールド
float4x4 matVP  : VIEWPROJECTION;

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
void GouraudVS(float3 InPos : POSITION,
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
    float B = saturate(dot(L, N));
    // if(B < 0.2f){B = 0.2f;}else{B = 0.5f;}
    OutDiff = I_a * k_a + I_d * k_d * B;
    OutSpec = I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
    OutTex = InTex;
}

// ピクセルシェーダ
void GouraudPS(float4 InDiff : COLOR0,
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

// 頂点シェーダ(ピクセル毎のシェーディング)
void PhongVS(float4 InPos : POSITION,
             float3 InNor : NORMAL,
             float2 InTex : TEXCOORD0,
             out float4 OutPos  : POSITION,
             out float2 OutTex  : TEXCOORD0,
             out float3 OutWPos : TEXCOORD1,
             out float3 OutWNor : TEXCOORD2)
{
    OutPos = mul(InPos, matWVP);
    OutTex = InTex;
    OutWPos = mul(InPos, matW).xyz;
    OutWNor = mul(InNor, (float3x3)matW);
}

// ピクセルシェーダ(ピクセル毎のシェーディング)
void PhongPS(float2 InTex : TEXCOORD0,
             float3 InPos : TEXCOORD1,
             float3 InNor : TEXCOORD2,
             out float4 OutCol : COLOR0)
{
    float3 L = normalize(-light);
    float3 N = normalize(InNor);
    float3 V = normalize(camera - InPos);
    float3 R = reflect(-V, N);
    OutCol = I_a * k_a + I_d * k_d * saturate(dot(L, N));
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    OutCol += I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
}

// ピクセルシェーダ(ブリン シェーディング)
void BlinnPS(float2 InTex : TEXCOORD0,
             float3 InPos : TEXCOORD1,
             float3 InNor : TEXCOORD2,
             out float4 OutCol : COLOR0)
{
    float3 L = normalize(-light);
    float3 N = normalize(InNor);
    float3 V = normalize(camera - InPos);
    //float3 R = reflect(-V, N);
    float3 H = normalize(V + L);
    OutCol = I_a * k_a + I_d * k_d * saturate(dot(L, N));
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    OutCol += I_s * k_s * pow(saturate(dot(N, H)), k_p);
}

// ピクセルシェーダ(クック・トランス シェーディング)
void CookTorrancePS(float2 InTex : TEXCOORD0,
                    float3 InPos : TEXCOORD1,
                    float3 InNor : TEXCOORD2,
                    out float4 OutCol : COLOR0)
{
    float3 L = normalize(-light);
    float3 N = normalize(InNor);
    float3 V = normalize(camera - InPos);
    float3 H = normalize(V + L);
    float NL = dot(N, L);
    OutCol = I_a * k_a + I_d * k_d * saturate(NL);
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    float NH = dot(N, H);
    float NH2 = NH * NH;
    float m = 0.35f;
    float m2 = m * m;
    float D = exp(-((1.0f - NH2) / NH2) / m2) /
                (4.0f * m2 * NH2 * NH2);
    float NV = dot(N, V);
    float VH = dot(V, H);
    float G = min(min(2.0f * NH * NV / VH,
                      2.0f * NH * NL / VH), 1);
    float c = dot(L, H);
    float n = 10.0f;
    float g = sqrt(n * n + c * c - 1.0f);
    float gpc = g + c;
    float gmc = g - c;
    float i = gmc / gpc;
    float j = (c * gpc - 1.0f) / (c * gmc + 1.0f);
    float F = 0.5f * i * i * (1.0f + j * j);
    OutCol += I_s * k_s * pow(saturate(D * G * F / NV), k_p);
}

// ピクセルシェーダ(トゥーンシェーディング)
void ToonPS(float2 InTex : TEXCOORD0,
            float3 InPos : TEXCOORD1,
            float3 InNor : TEXCOORD2,
            out float4 OutCol : COLOR0)
{
    float3 L = normalize(-light);
    float3 N = normalize(InNor);
    float3 V = normalize(camera - InPos);
    float3 R = reflect(-V, N);
    float i = dot(L, N);
    if (i < 0.2f)
        i = 0.8f;
    else
        i = 1.0f;
    OutCol = I_a * k_a + I_d * k_d * i;
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    //OutCol += I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
}

// 頂点シェーダ(輪郭線描画)
void EdgeVS(float4 InPos : POSITION,
            float3 InNor : NORMAL,
            out float4 OutPos : POSITION)
{
    float3 P = mul(InPos, matW).xyz;
    float3 N = mul(InNor, (float3x3)matW);
    P += N * weight;
    OutPos = mul(float4(P, 1.0f), matVP);
}

// ピクセルシェーダ(輪郭線描画)
void EdgePS(out float4 OutCol : COLOR0)
{
    OutCol = float4(0.0f, 0.0f, 0.0f, 1.0f);
}

// フォン シェーディング
technique TPhong
{
    // パス
    pass P0
    {
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader = compile ps_3_0 PhongPS();
    }
}

// トゥーンシェーディング
technique TToon
{
    // パス
    pass P0
    {
        CullMode = CCW;
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader = compile ps_3_0 ToonPS();
    }
    pass P1
    {
        CullMode = CW;
        VertexShader = compile vs_3_0 EdgeVS();
        PixelShader = compile ps_3_0 EdgePS();
    }
}

// ブリン シェーディング
technique TBlinn
{
    // パス
    pass P0
    {
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader = compile ps_3_0 BlinnPS();
    }
}

// クック・トランス シェーディング
technique TCookTorrance
{
    // パス
    pass P0
    {
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader = compile ps_3_0 CookTorrancePS();
    }
}

// グロー シェーディング
technique TGouraud
{
    // パス
    pass P0
    {
        VertexShader = compile vs_3_0 GouraudVS();
        PixelShader = compile ps_3_0 GouraudPS();
    }
}