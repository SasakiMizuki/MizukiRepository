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
float4x4 matVP	: VIEWPROJECTION;

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

// 輪郭線の太さ
float	thickness = 0.7f;

// サンプラステート
sampler Sampler = sampler_state
{
    Texture = (tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// トゥーンシェーディング(VS)
// (Phoneシェーディングと同じ)
void ToonVS(float4 InPos : POSITION,
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

// トゥーンシェーディング
void ToonPS(float2 InTex : TEXCOORD0,
            float3 InPos : TEXCOORD1,
			float3 InNor : TEXCOORD2,
			out float4 OutCol : COLOR0)
{
	float3 L = normalize(-light);
	float3 N = normalize(InNor);
	float3 V = normalize(camera - InPos);
	float3 R = reflect(-V, N);
	//float B = saturate(dot(L, N));
	float B = dot(L, N);

	// if文で2階調に
	if (B < 0.3f)
		B = 0.6f;
	else 
		B = 1.0f;

    OutCol = I_a * k_a + I_d * k_d * B;
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
	//OutCol += I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
}

// 頂点シェーダ(輪郭線描画)
void EdgeVS(float4 InPos : POSITION,
	float3 InNor : NORMAL,
	out float4 OutPos : POSITION) {

	float3 P = InPos.xyz + InNor * thickness;
	OutPos = mul(float4(P, 1), matWVP);
}

// ピクセルシェーダ(輪郭線描画)
void EdgePS(out float4 OutCol : COLOR0) {
	OutCol = float4(0.0f, 0.0f, 0.0f, 1.0f);
}

// フォン シェーディング
technique TToon
{
    // パス
    pass P0
    {
		CullMode = CCW;
        VertexShader = compile vs_3_0 ToonVS();
        PixelShader = compile ps_3_0 ToonPS();
    }
	pass P1
	{
		CullMode = CW;
		VertexShader = compile vs_3_0 EdgeVS();
		PixelShader = compile ps_3_0 EdgePS();
	}
}