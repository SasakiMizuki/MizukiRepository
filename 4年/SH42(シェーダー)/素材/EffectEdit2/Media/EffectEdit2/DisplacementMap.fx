// ディスプレースメント マッピング (EffectEdit2用)
//
string XFile = "Bump/square2.x";

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
texture Tex < string Name = "Bump/stones.bmp"; >;               // 通常テクスチャ
texture NormalMap < string Name = "Bump/stones_NM_height.tga"; >;   // 法線マップ テクスチャ

float MaxHeight = 0.05f;            // 高さ最大値
float Division = 0.002f;            // 分割率

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

// フォンの反射モデル (頂点シェーダ)
void PhongVS(float3 InPos  : POSITION,
             float3 InNorm : NORMAL,
             float2 InTex  : TEXCOORD0,
             out float4 OutPos      : POSITION,
             out float2 OutTex      : TEXCOORD0,
             out float3 OutPosForPS : TEXCOORD1,
             out float3 OutNorm     : TEXCOORD2)
{
    OutPos      = mul(float4(InPos, 1), WorldViewProj);     // 頂点座標 (射影空間)
    OutTex      = InTex;                                    // テクスチャ座標
    OutPosForPS = mul(float4(InPos, 1), World).xyz;             // 頂点座標 (ワールド空間)
    OutNorm     = normalize(mul(InNorm, (float3x3)World));  // 法線ベクトル (ワールド空間)
}

// ディスプレースメント マップ (頂点シェーダ)
void DisplacementVS(float3 InPos  : POSITION,
                    float3 InTan  : TANGENT,
                    float3 InNorm : NORMAL,
                    float2 InTex  : TEXCOORD0,
                    out float4 OutPos      : POSITION,
                    out float2 OutTex      : TEXCOORD0,
                    out float3 OutPosForPS : TEXCOORD1,
                    out float3 OutNorm     : TEXCOORD2)
{
    float4 NH = tex2Dlod(NormalSampler, float4(InTex, 0, 1));   // 高さ
    InPos += InNorm * NH.w * MaxHeight - 0.5f * MaxHeight;;
    OutPos      = mul(float4(InPos, 1), WorldViewProj);     // 頂点座標 (射影空間)
    OutTex      = InTex;                                    // テクスチャ座標
    OutPosForPS = mul(float4(InPos, 1), World).xyz;             // 頂点座標 (ワールド空間)

    float3 BiNormal = cross(InTan, InNorm);                 // 従法線を求める
    float3 T = normalize(mul(InTan, (float3x3)World));      // 接ベクトル (ワールド空間)
    float3 B = normalize(mul(BiNormal, (float3x3)World));   // 従法線ベクトル (ワールド空間)
    float3 N = normalize(mul(InNorm, (float3x3)World));     // 法線ベクトル (ワールド空間)
    float3 NewNorm = NH.xyz * 2.0f - 1.0f;
    OutNorm.x = dot(NewNorm, B);                            // 法線ベクトル (ワールド空間)
    OutNorm.y = dot(NewNorm, -T);
    OutNorm.z = dot(NewNorm, N);
}

// フォンの反射モデル (ピクセルシェーダ)
void PhongPS(float2 InTex  : TEXCOORD0,
             float3 InPos  : TEXCOORD1,
             float3 InNorm : TEXCOORD2,
             out float4 OutCol : COLOR)
{
    float3 L = normalize(-lightDir);            // 光源へのベクトル
    float3 N = normalize(InNorm);               // 法線ベクトル
    float3 V = normalize(CameraPos - InPos);    // 視点へのベクトル
    float3 R = reflect(-V, N);                  // 反射ベクトル

    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // 拡散色 + 環境色
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25);   // 鏡面反射色

    OutCol = tex2D(TexSampler, InTex) * Diff + Spec;
}

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
    float3 BiNormal = cross(InTan, InNorm);                 // 従法線を求める
    float4 P = mul(float4(InPos, 1), World);                // 頂点座標 (ワールド空間)
    float3 T = normalize(mul(InTan, (float3x3)World));      // 接ベクトル (ワールド空間)
    float3 B = normalize(mul(BiNormal, (float3x3)World));   // 従法線ベクトル (ワールド空間)
    float3 N = normalize(mul(InNorm, (float3x3)World));     // 法線ベクトル (ワールド空間)
    float3 V = normalize(CameraPos - P.xyz);                    // 視点へのベクトル (ワールド空間)
    float3 L = normalize(-lightDir);                        // 光源へのベクトル (ワールド空間)
    OutView.x = dot(V, B);                                  // 視点へのベクトル (接空間)
    OutView.y = dot(V, T);
    OutView.z = dot(V, N);
    OutLight.x = dot(L, B);                                 // 光源へのベクトル (接空間)
    OutLight.y = -dot(L, T);    // (どこかにバグが!?)
    OutLight.z = dot(L, N);
}

// バンプマッピング (ピクセルシェーダ)
void BumpMapPS(float2 InTex   : TEXCOORD0,
               float3 InLight : TEXCOORD1,
               float3 InView  : TEXCOORD2,
               out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);                          // 光源へのベクトル (接空間)
    float3 N = tex2D(NormalSampler, InTex).rgb * 2.0f - 1.0f;       // 法線ベクトル (接空間)
    N = normalize(N);
    float3 V = normalize(InView);                           // 視点へのベクトル (接空間)
    float3 R = reflect(-V, N);                              // 反射ベクトル (接空間)
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // 拡散光
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // 鏡面反射光
    OutCol = tex2D(TexSampler, InTex) * Diff + Spec;        // 最終的な色
}

// 視差マッピング (ピクセルシェーダ)
void ParalluxMapPS(float2 InTex   : TEXCOORD0,
                   float3 InLight : TEXCOORD1,
                   float3 InView  : TEXCOORD2,
                   out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);                          // 光源へのベクトル (接空間)
    float3 V = normalize(InView);                           // 視点へのベクトル (接空間)
    float  H = tex2D(NormalSampler, InTex).a;                   // 高さ取得
    float2 Tex = InTex + V.xy * H * MaxHeight;              // UV座標をずらす
    float3 N = (float3)tex2D(NormalSampler, Tex) * 2.0f - 1.0f; // 法線ベクトル (接空間)
    N = normalize(N);
    float3 R = reflect(-V, N);                              // 反射ベクトル (接空間)
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // 拡散光
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // 鏡面反射光
    OutCol = tex2D(TexSampler, Tex) * Diff + Spec;          // 最終的な色
}

// 視差遮蔽マッピング (ピクセルシェーダ)
void POMapPS(float2 InTex   : TEXCOORD0,
             float3 InLight : TEXCOORD1,
             float3 InView  : TEXCOORD2,
             out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);      // 光源へのベクトル (接空間)
    float3 V = normalize(InView);       // 視点へのベクトル (接空間)
    float2 dx = ddx(InTex);             // x方向の勾配
    float2 dy = ddy(InTex);             // y方向の勾配
    float4 NH = float4(0, 0, 1, 1);     // 法線ベクトル&高さ (接空間)
    float2 offset = V.xy * Division;    // サンプリング位置のオフセット値
    float2 Tex = InTex;                 // サンプリング位置
    float height = MaxHeight;                // 
    while (height > 0.0f) {
        NH = tex2Dgrad(NormalSampler, Tex, dx, dy); // 
        if (NH.a * MaxHeight >= height)         // 
            break;
        Tex -= offset;                          // 
        height -= V.z * Division;               // 
    }
    float3 N = normalize((float3)NH * 2.0f - 1.0f);                 // 法線ベクトル
    float3 R = reflect(-V, N);                                      // 反射ベクトル
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // 拡散光
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // 鏡面反射光
    OutCol = tex2Dgrad(TexSampler, Tex, dx, dy) * Diff + Spec;      // 最終的な色
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

// 視差マッピング
technique TParallaxMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpMapVS();
        PixelShader  = compile ps_3_0 ParalluxMapPS();
    }
}

// 視差遮蔽マッピング
technique TParallaxOcclusionMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpMapVS();
        PixelShader  = compile ps_3_0 POMapPS();
    }
}

// ディスプレースメント マッピング
technique TDisplacementMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 DisplacementVS();
        PixelShader  = compile ps_3_0 PhongPS();
    }
}

// フォン シェーディング
technique TPhong
{
    pass P0
    {
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader  = compile ps_3_0 PhongPS();
    }
}