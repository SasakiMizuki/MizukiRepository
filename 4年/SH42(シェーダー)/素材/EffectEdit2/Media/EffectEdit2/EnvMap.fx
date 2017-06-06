// EnvMap.fx
// 環境マッピング
// ティーポットに写りこみを描く

// モデル
string XFile = "misc/teapot2.x";

// 変換用マトリックス
float4x4 WorldView : WORLDVIEW;
float4x4 WorldViewProjection : WORLDVIEWPROJECTION;

// カメラ位置
float3 CameraPos : CAMERAPOSITION;    

// ライトの方向（ビュー空間）
float3 lightDir < string UIDirectional = "Light Direction1"; > = {0.0, 0.0, 1.0};

// 環境マップ
string Environment = "Lobby/lobbycube.dds";     // environment map

// マテリアル
float4 MaterialDiffuseColor     = { 0.4f, 0.4f, 0.4f, 1.0f };    // diffuse
float4 MaterialSpecularColor    = { 0.2f, 0.2f, 0.2f, 1.0f };    // specular
float  MaterialSpecularPower    = 32;                            // power

// 環境マップの作成
// キューブテクスチャを設定
// ファイル名の指定
texture EnvironmentMap 
< string type = "CUBE"; string name = "Lobby/lobbycube.dds"; >;

// 3Dサンプラの指定
samplerCUBE EnvironmentSampler = sampler_state
{ 
    Texture = (EnvironmentMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// -------------------------------------------------------------
// シェーダの出力フォーマットを定義
struct EnvMap_VS_OUTPUT
{
    float4 Pos   : POSITION;
    float4 Diff  : COLOR0;     // ディフーズ
    float4 Spec  : COLOR1;       // スペキュラ
    float3 CubeTexcoord : TEXCOORD0;
};

// -------------------------------------------------------------
// 頂点シェーダ
EnvMap_VS_OUTPUT EnvMap_vs_main(
    float4  Pos   : POSITION,
    float3  Normal: NORMAL)
{
    EnvMap_VS_OUTPUT   Out;
    // 出力用の座標変換
    Out.Pos = mul(Pos, WorldViewProjection);

    // 照明計算用の座標変換
    float4 P = mul(Pos,WorldView);
    float4 N = mul(Normal,WorldView);
    // 視線ベクトル
    float3 V = normalize(CameraPos - P);
    float3 R = normalize(reflect(lightDir, N));

    // ディフューズライト
    float4 Diff_Light = MaterialDiffuseColor * max(0, dot( N, -lightDir));

    // スペキュラライト
    float4 Spec_Light = MaterialSpecularColor 
                * pow(max(0, dot(R, V)), MaterialSpecularPower/4);

    Out.Diff = 1.0 * Diff_Light;
    Out.Spec = 1.0 * Spec_Light;
    // 反射ベクトルの計算
    Out.CubeTexcoord = reflect(-V, N);
//    Out.CubeTexcoord = Pos;

    return Out;
}

// ピクセルシェーダ
float4 EnvMap_ps_main(     
    float4 Pos  : POSITION,
    float4 Diff : COLOR0,
    float4 Spec : COLOR1,
    float3 CubeTexcoord : TEXCOORD0) : COLOR
{
    float4 OutColor;

    OutColor = Diff;
    // ディフーズと環境テクスチャの混合割合を調整
    OutColor += 1.0*lerp(OutColor, texCUBE(EnvironmentSampler, CubeTexcoord), 0.8);
    OutColor += Spec;

    return OutColor;
}


technique EnvMap
{
    pass P0
    {
        VertexShader = compile vs_2_0 EnvMap_vs_main();
        PixelShader  = compile ps_2_0 EnvMap_ps_main();
    }
}