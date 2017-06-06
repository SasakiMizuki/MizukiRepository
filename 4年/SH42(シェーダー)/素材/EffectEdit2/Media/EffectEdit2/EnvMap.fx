// EnvMap.fx
// ���}�b�s���O
// �e�B�[�|�b�g�Ɏʂ肱�݂�`��

// ���f��
string XFile = "misc/teapot2.x";

// �ϊ��p�}�g���b�N�X
float4x4 WorldView : WORLDVIEW;
float4x4 WorldViewProjection : WORLDVIEWPROJECTION;

// �J�����ʒu
float3 CameraPos : CAMERAPOSITION;    

// ���C�g�̕����i�r���[��ԁj
float3 lightDir < string UIDirectional = "Light Direction1"; > = {0.0, 0.0, 1.0};

// ���}�b�v
string Environment = "Lobby/lobbycube.dds";     // environment map

// �}�e���A��
float4 MaterialDiffuseColor     = { 0.4f, 0.4f, 0.4f, 1.0f };    // diffuse
float4 MaterialSpecularColor    = { 0.2f, 0.2f, 0.2f, 1.0f };    // specular
float  MaterialSpecularPower    = 32;                            // power

// ���}�b�v�̍쐬
// �L���[�u�e�N�X�`����ݒ�
// �t�@�C�����̎w��
texture EnvironmentMap 
< string type = "CUBE"; string name = "Lobby/lobbycube.dds"; >;

// 3D�T���v���̎w��
samplerCUBE EnvironmentSampler = sampler_state
{ 
    Texture = (EnvironmentMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// -------------------------------------------------------------
// �V�F�[�_�̏o�̓t�H�[�}�b�g���`
struct EnvMap_VS_OUTPUT
{
    float4 Pos   : POSITION;
    float4 Diff  : COLOR0;     // �f�B�t�[�Y
    float4 Spec  : COLOR1;       // �X�y�L����
    float3 CubeTexcoord : TEXCOORD0;
};

// -------------------------------------------------------------
// ���_�V�F�[�_
EnvMap_VS_OUTPUT EnvMap_vs_main(
    float4  Pos   : POSITION,
    float3  Normal: NORMAL)
{
    EnvMap_VS_OUTPUT   Out;
    // �o�͗p�̍��W�ϊ�
    Out.Pos = mul(Pos, WorldViewProjection);

    // �Ɩ��v�Z�p�̍��W�ϊ�
    float4 P = mul(Pos,WorldView);
    float4 N = mul(Normal,WorldView);
    // �����x�N�g��
    float3 V = normalize(CameraPos - P);
    float3 R = normalize(reflect(lightDir, N));

    // �f�B�t���[�Y���C�g
    float4 Diff_Light = MaterialDiffuseColor * max(0, dot( N, -lightDir));

    // �X�y�L�������C�g
    float4 Spec_Light = MaterialSpecularColor 
                * pow(max(0, dot(R, V)), MaterialSpecularPower/4);

    Out.Diff = 1.0 * Diff_Light;
    Out.Spec = 1.0 * Spec_Light;
    // ���˃x�N�g���̌v�Z
    Out.CubeTexcoord = reflect(-V, N);
//    Out.CubeTexcoord = Pos;

    return Out;
}

// �s�N�Z���V�F�[�_
float4 EnvMap_ps_main(     
    float4 Pos  : POSITION,
    float4 Diff : COLOR0,
    float4 Spec : COLOR1,
    float3 CubeTexcoord : TEXCOORD0) : COLOR
{
    float4 OutColor;

    OutColor = Diff;
    // �f�B�t�[�Y�Ɗ��e�N�X�`���̍��������𒲐�
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